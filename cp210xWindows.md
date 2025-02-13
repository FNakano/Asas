# Instalação do driver para CP210X no Windows

## Introdução

Deve haver muitos jeitos de instalar drivers no Windows 11. Este é apenas um jeito que funcionou.

O driver em questão é para CP2102, CP2109 (referenciados como CP210X) que são pontes (bridge) USB para serial (RS232). Pontes são conversores de protocolos. CP210X faz a conversão de sinais no protocolo USB para o protocolo serial. Este protocolo é usado por microcontroladores como ATMega328 (Arduino), ESP8266 (NodeMCU), ESP32 (Node32S).

Há outros componenentes com função equivalente ao CP210X, como CH340 e FTDI232. Cada componente tem driver específico.

Em uma frase, o roteiro a seguir mostra como verificar se o driver está instalado, como não está, mostra como baixar o driver do site do fabricante e como instalar o driver baixado no Windows 11.

Clique sobre o ícone do Windows na barra de tarefas e procure por *dispositivos*

![](./images/Captura%20de%20tela%202025-02-11%20152905.png)

Uma das respostas é o Gerenciador de Dispositivos, abra-o, clicando no link.

![](./images/Captura%20de%20tela%202025-02-11%20152959.png)

Se o dispositivo não estiver conectado na USB ele não aparece na lista de dispositivos. Conecte o dispositivo (no caso é um Node32S) em alguma porta USB. O dispositivo aparecerá em *Outros dispositivos* com um sinal de alerta. No caso, sabe-se que o alerta deve-se à falta do driver. Este pode ser baixado gratuitamente em https://www.silabs.com/developer-tools/usb-to-uart-bridge-vcp-drivers. Neste caso foi feita uma busca pelo driver.

![](./images/Captura%20de%20tela%202025-02-11%20153045.png)

Na aba *Downloads* escolha o ítem *CP210x Universal Windows Driver* o arquivo zip contendo o driver será baixado em seu computador.

![](./images/Captura%20de%20tela%202025-02-11%20153150.png)

Localize o arquivo baixado e extraia seu conteúdo em uma pasta. O menu com a opção *extrair* aparece clicando no arquivo com o botão da direita do mouse. É necessário extrair porque o Windows não instala drivers diretamente de arquivos .zip .

![](./images/Captura%20de%20tela%202025-02-11%20153238.png)

Volte ao gerenciador de dispositivos e clique sobre o ítem com o sinal de alerta. Uma janela contendo detalhes sobre o dispositivo é aberta.

![](./images/Captura%20de%20tela%202025-02-11%20153300.png)

Clique no botão *Atualizar driver*

![](./images/Captura%20de%20tela%202025-02-11%20153444.png)

Escolha a opção *Procurar drivers no meu computador*. Uma outra janela que permite selecionar pastas e procurar nelas é aberta. Clique em *Procurar*, selecione a pasta onde extraiu o conteúdo do .zip e clique em *OK*.

![](./images/Captura%20de%20tela%202025-02-11%20153612.png)

O driver é instalado e, se a instalação ocorreu sem problemas, o estado do dispositivo muda para *Este dispositivo está funcionando corretamente*.

![](./images/Captura%20de%20tela%202025-02-11%20153640.png)

![](./images/Captura%20de%20tela%202025-02-11%20153701.png)

![](./images/Captura%20de%20tela%202025-02-11%20153741.png)

![](./images/Captura%20de%20tela%202025-02-11%20153820.png)

![](./images/Captura%20de%20tela%202025-02-11%20153927.png)

Para testar a comunicação, abra algum aplicativo que se comunique com o Node32S (no caso usamos Thonny)

![](./images/Captura%20de%20tela%202025-02-11%20154043.png)

