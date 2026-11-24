# Примеры работ: jane.doe

Имя папки — имя и фамилия студента, не GitHub-логин. Логин может отличаться.

## Задание 1. Масса шкафа

Файлы: `1/main.c`, `1/examplefile.c`. Это пример программы из нескольких
исходных файлов:

- `main.c` — ввод данных, проверка диапазонов, вывод результата;
- `examplefile.c` — функции `shelf_count`, `volume_m3`, `wardrobe_mass`.

Ввод: высота `h` (180–220 см), ширина `w` (80–120 см), глубина `d` (50–90 см),
затем три плотности в `кг/м3`: ДСП, ДВП, дерево. Число полок считается как
`h / 40` с округлением вниз. Размеры переводятся в метры, итоговая масса
выводится в килограммах.

Компиляция: в команду передаются оба `.c`-файла, заголовок не нужен —
прототипы функций объявлены в `main.c`.

```
cd jane.doe\1
gcc main.c examplefile.c -o wardrobe.exe
wardrobe.exe
```

В PowerShell: `.\wardrobe.exe`. В Linux/macOS:
`gcc main.c examplefile.c -o wardrobe && ./wardrobe`.

Пример ввода:

```
200 100 70 650 750 700
```

Программа выведет число полок и массу шкафа.

## Отправка задания

Репозиторий публичный. Сделайте fork <https://github.com/hsgapworks/students>,
клонируйте свой fork и добавьте upstream:

```
git remote add upstream https://github.com/hsgapworks/students.git
```

Пример для задания 1 (команды выполняются в корне fork'а):

```
git checkout main
git fetch upstream
git merge upstream/main
git checkout -b jane-task1
git add 1/
git commit -m "Task 1"
git push -u origin jane-task1
```

Pull request создаётся в `hsgapworks/students`: `base repository` =
`hsgapworks/students`, `base` = `main`, `head repository` = ваш fork,
`compare` = `jane-task1`. Через `gh`:

```
gh pr create --repo hsgapworks/students --base main --head <ВашЛогин>:jane-task1 --title "Jane Doe - task 1" --body "Task 1"
```

Для каждого следующего задания создавайте отдельную ветку, например
`jane-task2`, и добавляйте соответствующую папку (`git add 2/`). Пошаговые
команды создания ветки уже приведены выше в этом разделе — строка
`git checkout -b jane-task1`; в корневом `README.md` они разобраны в разделе
«Как сдать задание: pull request». Перед следующим заданием синхронизируйте fork:

```
git checkout main
git fetch upstream
git merge upstream/main
git push origin main
```
