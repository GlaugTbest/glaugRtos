Este código usa o FreeRTOS para controlar um LED com base no pressionamento de um botão. A ideia é que, quando o botão é pressionado, o LED acende após um atraso de 100 ms. Se o botão não for pressionado, o LED fica apagado.

Passos principais:
Inicialização: O código configura o pino do LED como saída e o pino do botão como entrada com um resistor de pull-up.

Tarefa: Uma tarefa no FreeRTOS verifica constantemente o estado do botão. Quando o botão é pressionado, o LED acende após 100 ms.

Loop principal: O código entra em um loop infinito após iniciar o FreeRTOS, aguardando interrupções.

Em resumo, o LED acende ao pressionar o botão, com um pequeno atraso, e apaga quando o botão não está pressionado.
