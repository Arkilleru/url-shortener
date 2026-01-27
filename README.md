**This repository is for userver v2.8 or older versions. For newer versions of userver please use 
[userver-create-service](https://userver.tech/de/dab/md_en_2userver_2build_2build.html#autotoc_md177) script.**

# URL Shortener Service

Высокопроизводительный асинхронный сокращатель ссылок на базе фреймворка [userver](https://github.com/userver-framework/userver).


## Реализованный функционал
* **Blacklist Filtering:** Быстрая фильтрация вредоносных доменов с использованием **Hash Set** (`std::unordered_set`) — сложность поиска $O(1)$.
* **Thread-safe Storage:** Хранилище в памяти с использованием `std::shared_mutex` (Read-Write Lock) для обеспечения конкурентного доступа.
* **HTTP API:** - `POST /v1/shorten` — создание ссылки.
    - `GET /v1/shorten` — редирект (302 Found).
* **Testing:** Покрытие базовых сценариев (создание, редирект, черный список) через pytest.

## Сборка и запуск
Сервис построен на базе userver, который стабильно работает на большинстве Linux-дистрибутивов (Ubuntu, Fedora, Debian, Alpine). Хотя основной метод запуска — Docker, возможна локальная сборка на поддерживаемых системах

склонировать репозиторий:
* ```git clone https://github.com/Arkilleru/url-shortener.git```


Параметр PRESET определяет режим сборки: debug (для отладки) или release (для максимальной производительности).

* `make cmake-PRESET` — запустить настройку CMake, обновить параметры и списки исходных файлов.

* `make build-PRESET` — собрать сервис (компиляция).

* `make test-PRESET` — собрать сервис и запустить все тесты.

* `make start-PRESET` — собрать сервис и оставить его запущенным в тестовом окружении.

* `make install-PRESET` — установить собранный проект в директорию PREFIX.

* `make format` — автоматически отформатировать весь исходный код (C++ и Python).

* `make dist-clean` — полная очистка: удалить файлы сборки и кэш CMake.

* `make docker-COMMAND` — запустить любую из вышеперечисленных команд внутри Docker-контейнера (например, make docker-test-debug).

* `make docker-clean-data` — остановить и удалить Docker-контейнеры проекта

## Команды

Для тестирования используйте утилиту `curl` в терминале. Если запуск идёт с использованием докер контейнера, то команды вводятся только в терминале самого контейнера.

### 1. Создание короткой ссылки (POST)
Отправьте URL, который хотите сократить. В ответ сервис пришлет ID вашей ссылки.
```bash
curl -i -X POST "http://localhost:8080/v1/shorten?url=[https://google.com](https://google.com)"
```

### 2. Переход по ссылке (GET)
Проверьте редирект (302 Found) на оригинальный сайт.
```bash
curl -i -X GET "http://localhost:8080/v1/shorten?id=ID""
```
## License

The original template is distributed under the [Apache-2.0 License](https://github.com/userver-framework/userver/blob/develop/LICENSE)
and [CLA](https://github.com/userver-framework/userver/blob/develop/CONTRIBUTING.md). Services based on the template may change
the license and CLA.
