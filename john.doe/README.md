# Примеры работ: john.doe

Имя папки — имя и фамилия студента, не GitHub-логин. Логин может отличаться.

## Задание 2. Угадай число

Файлы: `2/main.c`.

Программа работает в двух режимах.

- Режим 1: программа загадывает случайное число от 1 до 1000, пользователь
  вводит отгадки. Программа сообщает `The number is greater`,
  `The number is smaller` или `Correct! Attempts: N`.
- Режим 2: пользователь загадывает число, программа находит его бинарным
  поиском. Пользователь отвечает `>`, `<` или `=`. Программа выводит свою
  отгадку и число попыток.

Случайное число в режиме 1 инициализируется через `srand(time(NULL))`.
Проверка диапазона отгадок и обработка некорректного ввода предусмотрены.
Если ответы в режиме 2 противоречивы, программа сообщает об этом.

Компиляция и запуск в Windows. Откройте папку `2` во встроенном терминале
VS Code (`Ctrl+backtick`: `backtick` — обратный апостроф, символ `` ` ``)
или перейдите в неё через `cmd`:

```
cd john.doe\2
gcc main.c -o guess.exe
guess.exe
```

В PowerShell запуск: `.\guess.exe`. Математическая библиотека не нужна.

Пример работы, режим 2:

```
2
Think of a number from 1 to 1000: 73
Answer with >, < or =
500? <
250? <
125? <
63? >
94? <
78? <
70? >
74? <
72? >
73? =
Correct! Attempts: 9
```

В Linux/macOS:

```
gcc main.c -o guess
./guess
```

## Отправка задания

Репозиторий публичный. Сделайте fork <https://github.com/hsgapworks/students>,
клонируйте свой fork и добавьте upstream:

```
git remote add upstream https://github.com/hsgapworks/students.git
```

Пример для задания 2 (команды выполняются в корне fork'а):

```
git checkout main
git fetch upstream
git merge upstream/main
git checkout -b john-task2
git add 2/
git commit -m "Task 2"
git push -u origin john-task2
```

Pull request создаётся в `hsgapworks/students`: `base repository` =
`hsgapworks/students`, `base` = `main`, `head repository` = ваш fork,
`compare` = `john-task2`. Через `gh`:

```
gh pr create --repo hsgapworks/students --base main --head <ВашЛогин>:john-task2 --title "John Doe - task 2" --body "Task 2"
```

Перед следующим заданием синхронизируйте fork:

```
git checkout main
git fetch upstream
git merge upstream/main
git push origin main
```
