# импортируем numpy
import numpy as np
# создаем список случайных элементов
spisok = np.random.randint(1, 1000, size=(100))
# Выводим список (для проверки)
print(spisok)
# Выводим минимальный и максимальный элемент (для проверки)
print(np.max(spisok), np.min(spisok))
# Выводим ответ
print(np.max(spisok)-np.min(spisok))