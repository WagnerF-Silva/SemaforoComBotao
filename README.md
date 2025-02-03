# One Shot Timer para Raspberry Pi Pico

## Descrição
Este projeto implementa um temporizador de um disparo (*One Shot Timer*) para controle de LEDs usando o Raspberry Pi Pico. O sistema aciona os LEDs com base no clique de um botão e os desliga sequencialmente com um intervalo de 3 segundos entre cada estado. Durante a execução do temporizador, novas interações do botão são bloqueadas até a finalização da sequência.

## Funcionamento
1. O usuário pressiona o botão (GPIO 5).
2. Os três LEDs (GPIOs 11, 12 e 13) são acesos simultaneamente.
3. Após 3 segundos, o LED vermelho (GPIO 13) é desligado.
4. Após mais 3 segundos, o LED amarelo (GPIO 12) é desligado.
5. Após mais 3 segundos, o LED verde (GPIO 11) é desligado.
6. Quando todos os LEDs estão apagados, o sistema permite uma nova ativação do botão.

## Estrutura do Código
- **Inicialização dos GPIOs**: Configuração dos LEDs como saída e do botão como entrada com *pull-up* ativado.
- **Interrupção no botão**: Utiliza `gpio_set_irq_enabled_with_callback()` para detectar o pressionamento.
- **Funções de temporização**:
  - `turn_off_red()`: Desliga o LED vermelho e agenda o próximo estado.
  - `turn_off_yellow()`: Desliga o LED amarelo e agenda o próximo estado.
  - `turn_off_green()`: Desliga o LED verde e libera o sistema para nova ativação.
- **Mecanismo de bloqueio**: Durante a execução da sequência de temporização, novas interações do botão são ignoradas.

## Requisitos
- Raspberry Pi Pico
- SDK do Pico configurado
- Ferramenta de compilação para C/C++

## Como Compilar e Executar
1. Clone ou copie o código-fonte para seu ambiente de desenvolvimento.
2. Compile o código usando o SDK do Pico.
3. Transfira o binário para o Raspberry Pi Pico.
4. Pressione o botão para testar a execução do temporizador.

## Melhorias Futuras
- Implementação de um mecanismo de debounce mais avançado.
- Personalização dos tempos de delay.
- Inclusão de um LED RGB ao invés de LEDs individuais.

## Autor
Este código foi desenvolvido para fins educacionais e experimentais no uso do Raspberry Pi Pico com temporizadores e interrupções.

