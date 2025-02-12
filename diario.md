primeira reunião (16/01)
- apresentação de materiais (complementares ao projeto anterior) 
  - cintos;
  - calços de madeira;
  - abraçadeiras;
  - kit de costura;
- conversas sobre acionamento do servo;
  - esclarecimento sobre o PWM;
    - zero graus e 180 graus corresponde a que valores de PWM?
    - micropython começou a crashar;
  - encontramos um servo que não funciona;
- conversas sobre estratégia de desenvolvimento;
  - colocar um protótipo com uma pena para funcionar BEM;
  - colocar um protótipo com três penas para funcionar BEM;
- próximos passos;
  - procurar penas;
  - procurar calços do tamanho certo;

pré-reunião

- penas são caras
- existe uma estratégia para emendar penas
- o pacote de penas tem muitas penas
- substituir penas por folhagens de decoração
- comprar colas (instantânea e cola quente)
- encontrar calços do tamanho certo (no caso, encontrei de conduíte
- servo esquenta

segunda reunião (23/01)
- teste de servo levantando e abaixando penas
  - talvez um contrapeso ajude;
  - teste com bateria de 9V como contrapeso mostrou resultado promissor;
- a fixação da pena no eixo do motor, através do braço de articulação é muito trabalhoso;
- alerta sobre orientação da subida/descida das penas;
- calços;
- resultados;
  - faixa de valores de PWM é de (aprox.) 20 a 130;
  - servo não consegue levantar galho de 24g mas consegue levantar galho de 14g, algumas vezes, sem contrapeso.
  - galho verga muito.
  - os crashes do micropython parecem ser falta de energia;
- proximos passos;
  - sabendo a orientação certa da subida/descida, procurar calços adequados;
  - alimentar servos com fonte externa (ex. powerbank)
  
  pré-reunião
  
  - aumentar braço com pedaços de PCB. Tirar pena do centro do braço para desimpedir parafuso de fixação do braço no servo;
  - fixação feita com cola quente (pistola e bastão de silicone) ou com cola instantânea (à base de cianoacrilato)
  - talvez furadeira/parafusadeira seja útil na reunião;
  - documentação;
    - instalação do driver CP210x no Windows;
    - funcionamento do servo;
      - em que condições o rotor engripa;
      - o que fazer quando o rotor engripa;
      - aquecimento, consumo de energia, desligamento da porta USB;
  
