В файле "Base.h" описан базовый класс, чтобы использовать для своей файловой системы, необходимо создать файл .cpp под свою ФС (Пример - fat32.cpp), далее
импортировать зависимость #include "Base.h", создать свой класс, унаследовать Base и описать реализацию 2 вирутальных функций setClusterData и getClusterSize. Удачи!