# Syncope Messenger

## Описание проекта:
Репозиторий содержит код приложения-мессенджера, написанного на C++. Проект включает как клиентскую, так и серверную реализацию, с топологией "звезда" для клиентских соединений (один сервер, который знает все обо всех клиентах).

![image_2023-05-10_22-57-17](https://github.com/ash4rk/syncope-messenger/assets/30512240/82a7aa28-9ce0-4839-9228-cd227004bf4e)

Графический интерфейс был создан с помощью ImGui, а сетевое взаимодействие - с помощью библиотеки Boost. Сборка осуществляется с помощью CMake + Conan. Используемый протокол соединения - TCP.

Кроме того, был реализован собственный протокол общения клиент-сервер со следующими командами:
- "AUTH" для авторизации
- "SAY" для сообщений от клиентов серверу 
- "SHOUT" для сообщений от сервера всем клиентам
- "WHISPER" для сообщений отдельным клиентам.

[Документация](docs/protocol.md) со сценарием взаимодествия. Тело сообщений кодируется в base64.

## Сборка и компиляция:
Чтобы поставить на Ubuntu 22.04:
```
apt-get update
apt-get install git build-essential python3-pip cmake pkg-config
apt-get install libboost-all-dev libgl-dev libgl1-mesa-dev libx11-xcb-dev libfontenc-dev libice-dev libsm-dev libxaw7-dev libxcomposite-dev libxcursor-dev libxdamage-dev libxext-dev libxfixes-dev libxi-dev libxinerama-dev libxkbfile-dev libxmu-dev libxmuu-dev libxpm-dev libxrandr-dev libxrender-dev libxres-dev libxss-dev libxt-dev libxtst-dev libxv-dev libxvmc-dev libxxf86vm-dev libxcb-render0-dev libxcb-render-util0-dev libxcb-xkb-dev libxcb-icccm4-dev libxcb-image0-dev libxcb-keysyms1-dev libxcb-randr0-dev libxcb-shape0-dev libxcb-sync-dev libxcb-xfixes0-dev libxcb-xinerama0-dev libxcb-dri3-dev uuid-dev libxcb-cursor-dev libxcb-util-dev libglu1-mesa-dev
pip install conan==1.57.0
```
```
git clone https://github.com/ash4rk/syncope-messenger.git app
cd app
mkdir build
cd build
conan install .. -s build_type=Release
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build .
cd ..
```

## Запуск:
Сервер:
```
build/SyncopeServer/SyncopeServer
```
Клиент:
```
build/SyncopeClient/SyncopeClient
```
Валидные данные для авторизации admin:admin.
Регистрация новых пользователей не реализована.

## Диаграммы классов:

![tcp_connection_uml](https://github.com/ash4rk/syncope-messenger/assets/30512240/4a626019-2544-40c4-83c4-c7069281bacd)
![tcp_client_uml](https://github.com/ash4rk/syncope-messenger/assets/30512240/6c005301-1364-443e-b34f-b3416115a6ce)
![tcp_server_uml](https://github.com/ash4rk/syncope-messenger/assets/30512240/9b0f5053-49eb-4010-8f9e-2809c69828d2)

## Необходимые пакеты
- [cmake](https://cmake.org/)
- [conan](https://github.com/conan-io/conan)
### Зависимости (загружаются через conan)
- [imgui](https://github.com/ocornut/imgui), [glfw](https://github.com/glfw/glfw), [glew](http://github.com/nigels-com/glew) - графический интерфейс
- [boost](https://www.boost.org)- сетевое взаимодействие
- [spdlog](https://github.com/conan-io/conan-center-index) - логирование
