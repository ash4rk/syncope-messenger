# Syncope Messenger

## Описание проекта:
Репозиторий содержит код приложения-мессенджера, написанного на C++. Проект включает как клиентскую, так и серверную реализацию, с топологией "звезда" для клиентских соединений (один сервер, который знает все обо всех клиентах).

Графический интерфейс был создан с помощью ImGui, а сетевое взаимодействие - с помощью библиотеки Boost. Сборка осуществляется с помощью CMake + Conan. Используемый протокол соединения - TCP.

Кроме того, был реализован собственный протокол связи клиент-сервер со следующими командами:
- "AUTH" для авторизации
- "SAY" для сообщений от клиентов серверу 
- "SHOUT" для сообщений от сервера всем клиентам
- "WHISPER" для сообщений отдельным клиентам.

Тело сообщений кодируется в base64.

## Сборка и компиляция:
```
mkdir build
conan install -s build_type=Release
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build
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

## Необходимые пакеты
- [cmake](https://cmake.org/)
- [conan](https://github.com/conan-io/conan)
### Зависимости (загружаются через conan)
- [imgui](https://github.com/ocornut/imgui), [glfw](https://github.com/glfw/glfw), [glew](http://github.com/nigels-com/glew) - графический интерфейс
- [boost](https://www.boost.org)- сетевое взаимодействие
- [spdlog](https://github.com/conan-io/conan-center-index) - логирование
