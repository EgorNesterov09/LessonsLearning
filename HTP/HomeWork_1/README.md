GPT использовал только для проверки на всякий случай.
Пользовался материалом лекций, слайд 15 "Инвертирование i-го бита"
Поскольку число и маска могут быть unit8_t, unit16_t, unit32_t, unit64_t,
использовал два шаблонных параметра в функции. GPT предлагал void* и static_cast<uint8_t*> внутри функции.
Мне показалось, мой вариант лучше. 
Проходим в цикле по индексам массива, оращаясь через operator[] к указателю на память,
и к каждому элементу применяем XOR с маской для инвертирования выбранных битов.
Применение XOR будет инвертировать те биты, где маска равна 1.
Написал пару тестов для проверки и демонстрационный вывод.