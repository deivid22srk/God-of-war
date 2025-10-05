# God of War 2018 - Android Remake

Recriação do início do God of War (2018) para Android usando C++ e Vulkan API.

## Características

- **Engine 3D com Vulkan**: Renderização moderna usando a API Vulkan para Android
- **Sistema de Câmera**: Câmera 3D completa com rotação e movimento
- **Personagem Jogável**: Sistema de player com estados (idle, walking, attacking, blocking)
- **Controles Touch**: Suporte completo para touch screen
- **Shaders Customizados**: Vertex e Fragment shaders otimizados em SPIR-V

## Tecnologias

- **Linguagem**: C++17
- **API Gráfica**: Vulkan
- **NDK**: Android Native Development Kit
- **Build System**: CMake + Gradle
- **Mínimo SDK**: Android 7.0 (API 24)

## Estrutura do Projeto

```
app/src/main/
├── cpp/
│   ├── main.cpp              # Entry point da aplicação
│   ├── vulkan_renderer.cpp   # Sistema de renderização Vulkan
│   ├── game_engine.cpp       # Engine principal do jogo
│   ├── camera.cpp            # Sistema de câmera 3D
│   ├── player.cpp            # Lógica do personagem
│   └── shaders.cpp           # Shaders SPIR-V compilados
└── java/
    └── MainActivity.kt       # Activity principal Android
```

## Compilação

### Requisitos

- Android Studio Arctic Fox ou superior
- NDK 25.2.9519653
- CMake 3.22.1
- JDK 17

### Build Local

```bash
./gradlew assembleDebug
```

O APK será gerado em: `app/build/outputs/apk/debug/app-debug.apk`

### Build via GitHub Actions

O projeto inclui um workflow do GitHub Actions que compila automaticamente o APK em cada push ou pull request.

## Instalação

1. Baixe o APK da seção de releases ou artifacts do GitHub Actions
2. Ative "Fontes desconhecidas" nas configurações do Android
3. Instale o APK no seu dispositivo
4. Certifique-se de que seu dispositivo suporta Vulkan 1.0+

## Requisitos do Dispositivo

- Android 7.0 ou superior
- Suporte a Vulkan API 1.0+
- GPU com suporte a Vulkan

## Controles

- **Touch e arrastar**: Rotacionar câmera
- **Toque simples**: Interagir

## Licença

Este é um projeto educacional/fan-made. God of War é marca registrada da Sony Interactive Entertainment.

## Autor

Desenvolvido como demonstração técnica de engine 3D em Android com Vulkan.
