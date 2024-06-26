# Decimal

## Реализация собственной библиотеки decimal.h

### decimal.h - это библиотека, которая предоставляет возможность работы с числами с фиксированной точностью после запятой (дескриптивных числах) в языке программирования C. Она предоставляет тип данных decimal_t, который позволяет хранить и манипулировать десятичными числами с высокой точностью.

- Реализованные функции:

    - Арифметические операторы:
      
        *  Сложение - int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
        
        * Вычитание - int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)    
        
        * Умножение - int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
        
        * Деление - int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result)
        
            * Функции возвращают код ошибки:  
            - 0 - OK
  
            - 1 - число слишком велико или равно бесконечности
            
            - 2 - число слишком мало или равно отрицательной бесконечности
            
            - 3 - деление на 0
    
    - Операторы сравнение:

        * Меньше - int s21_is_less(s21_decimal, s21_decimal)
        
        * Меньше или равно - int s21_is_less_or_equal(s21_decimal, s21_decimal)
        
        * Больше - int s21_is_greater(s21_decimal, s21_decimal)
        
        * Больше или равно - int s21_is_greater_or_equal(s21_decimal, s21_decimal)
        
        * Равно - int s21_is_equal(s21_decimal, s21_decimal)
        
        * Не равно - int s21_is_not_equal(s21_decimal, s21_decimal)

            * Возвращаемое значение:
            
            - 0 - FALSE
            
            - 1 - TRUE

    - Преобразователи:
    
       * Из int - int s21_from_int_to_decimal(int src, s21_decimal *dst)
       
       * Из float - int s21_from_float_to_decimal(float src, s21_decimal *dst)
       
       * В int - int s21_from_decimal_to_int(s21_decimal src, int *dst)
       
       * В float - int s21_from_decimal_to_float(s21_decimal src, float *dst)
           
           * Возвращаемое значение - код ошибки:
           
           - 0 - OK
           
           - 1 - ошибка конвертации
    
    - Другие функции:
        
        * Округляет указанное Decimal число до ближайшего целого числа в сторону отрицательной бесконечности - int s21_floor(s21_decimal value, s21_decimal *result)
        
        * Округляет Decimal до ближайшего целого числа - int s21_round(s21_decimal value, s21_decimal *result)
        
        *    Возвращает целые цифры указанного Decimal числа; любые дробные цифры отбрасываются, включая конечные нули - int s21_truncate(s21_decimal value, s21_decimal *result)
        
        * Возвращает результат умножения указанного Decimal на -1 - int s21_negate(s21_decimal value, s21_decimal *result)
        
            * Возвращаемое значение - код ошибки:
            
            - 0 - OK
            
            - 1 - ошибка вычисления

### Запуск

1. Для запуска потребуется компилятор gcc и утилита gcov и библиотека check.h:

- Утилита gcov является частью GNU Compiler Collection (GCC) и предназначена для анализа покрытия кода программ на языке C и C++.
- gcov предоставляет информацию о том, какие строки кода были выполнены и какие остались неиспользованными во время выполнения программы. Она позволяет определить, насколько хорошо код тестируется и какие части кода нуждаются в дополнительных тестах.
- В процессе компиляции программы с флагом -coverage, GCC внедряет в исходный код дополнительный код, который собирает данные о покрытии во время выполнения программы. Затем gcov используется для анализа этих данных и создания отчетов о покрытии.
- Отчеты, сгенерированные gcov, включают информацию о количестве выполненных и невыполненных строк кода, процентах покрытия для каждой строки и функции, а также другие метрики покрытия кода. Эти отчеты могут быть использованы для определения участков кода, которые нуждаются в дополнительных тестах, и для оценки общего покрытия кода тестами.

    > Для ОС Windows:
    Установите MinGW:

    1) Загрузите и установите MinGW (Minimalist GNU for Windows) с официального сайта: https://mingw.ru
    
    2) При установке выберите компоненты, включающие GCC (C Compiler), Binutils (GNU Binary Utilities) и MSYS (Minimal SYStem)..
    
    3) Добавьте путь к MinGW в переменную среды PATH:

        3.1. Откройте "Свойства системы" (нажмите Win + Pause/Break, затем выберите "Дополнительные параметры системы").
        
        3.2. Перейдите на вкладку "Дополнительно" и нажмите на кнопку "Переменные среды".
        
        3.3. В разделе "Системные переменные" найдите переменную "Path" и нажмите на кнопку "Изменить".
        
        3.4. Добавьте путь к директории bin в установленном MinGW (например, C:\MinGW\bin) в качестве нового значения переменной PATH.
        
        3.5. Нажмите "ОК", чтобы сохранить изменения.

    4) Установите утилиту gcov:

        4.1. Откройте командную строку (нажмите Win + R, введите "cmd" и нажмите Enter).
        
        4.2. Выполните команду 

        `mingw-get install gcov` 
        
        для установки утилиты gcov с использованием установленного MinGW.
    
    5) Установите необходимые зависимости:

        5.1. Откройте командную строку (нажмите Win + R, введите "cmd" и нажмите Enter).
        
        5.2. Выполните команду `mingw-get install msys` , чтобы установить MSYS, который содержит необходимые инструменты для сборки и установки библиотек.
    
    6) Загрузите и скомпилируйте библиотеку check:

        6.1. Загрузите исходный код библиотеки check с официального сайта: https://libcheck.github.io/check/
        
        6.2. Распакуйте архив с исходным кодом.
        
        6.3. Откройте командную строку в папке с распакованными исходными файлами.
        
        6.4. Выполните следующие команды:
        
        ```
        ./configure
        make
        make install
        ```

    > Для ОС Linux: 
    ```
    sudo apt-get install gcc
    sudo apt-get install gcov
    sudo apt-get install check
    ```

2. Склонируйте репозиторий в удобную для вас диреторию

3. Для демонстрации работы собственной  реализации библиотеки decimal.h:

    3.1. Перейдите с директорию `/src/`

    3.2. Возможности Makefile:
       
        * make gcov_repor -  сгенерирует отчет (HTML) покрытия кода unit-тестами.
        
        * make test - прогонит unit-тесты и выведет результат в консоль.
        
        * make s21_decimal.a - сборка проекта.
        
        * make check - команда для проверки формата (выдаст ошибки по google формату если есть).
        
        * make format - команда для исправления ошибок формата (исправит файлы).
        
        * make reduild - пересобирает проектв   
        
        * make clean - удалит все исполняемые файлы.   
