#include <iostream>
#include "sqlite3.h"
#include "Iterator.h"
#include <time.h> 
#include <string>



void read_data(int count, sqlite3* db) {
	sqlite3_stmt* pStatement;

	const char* sql = "SELECT id, url, title, last_visit_time FROM urls ORDER BY last_visit_time";

	int execResult = sqlite3_prepare_v2(
		db,
		sql,
		-1,
		&pStatement,
		NULL
	);

	int k = 0;

	clock_t start = clock();


	while (k != count)
	{

		k++;
		int execResultStep = sqlite3_step(pStatement);
		if (execResultStep != SQLITE_ROW) {
			break;
		}

		int id = sqlite3_column_int(pStatement, 0);
		char* url = (char*)sqlite3_column_text(pStatement, 1);
		char* title = (char*)sqlite3_column_text(pStatement, 2);
		int64_t last_visit_time = sqlite3_column_int64(pStatement, 3);


		std::cout << "id " << id << std::endl;
		std::cout << "url " << url << std::endl;
		std::cout << "title " << title << std::endl;
		std::cout << "time " << last_visit_time << std::endl << std::endl;

	}




}


void delete_table_row(int row_id, sqlite3* db) {
	// Функция удаления строки по id
	sqlite3_stmt* pStatement;
	const char* sql = "DELETE FROM urls WHERE id = ?";

	int execResult = sqlite3_prepare_v2(
		db,
		sql,
		-1,
		&pStatement,
		NULL
	);

	sqlite3_bind_int(pStatement, 1, row_id);
	int execResultStep = sqlite3_step(pStatement);

	if (execResultStep != SQLITE_DONE) {
		std::cout << "Error query";
	}
}

void fill_table(sqlite3* db) {
	//Запись данных в таблицу для проверки скорости

	HistoryContainer container;

	for (int i = 0; i < 10000; i++) {

		container.Add(History(i, "http:\\example.com", "Some_Title"));
	}

	const char* new_sql = "INSERT INTO my_urls VALUES (?, ?, ?)";


	sqlite3_stmt* pStatement;
	int execResult = sqlite3_prepare_v2(
		db,
		new_sql,
		-1,
		&pStatement,
		NULL
	);

	Iterator<History>* iterator = container.GetIterator();


	sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);

	clock_t start = clock();
	for (iterator->First(); !iterator->IsDone(); iterator->Next()) {
		History obj = iterator->GetCurrent();
		sqlite3_bind_int(pStatement, 1, obj.id);
		sqlite3_bind_text(pStatement, 2, obj.url, -1, SQLITE_TRANSIENT);
		sqlite3_bind_text(pStatement, 3, obj.title, -1, SQLITE_TRANSIENT);
		int stepResult = sqlite3_step(pStatement);
		sqlite3_clear_bindings(pStatement);
		sqlite3_reset(pStatement);
	}

	sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);


	//const char* errmsg = sqlite3_errmsg(db);
	//std::cout << errmsg;

	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	std::cout << "Время выполнения программы - " << seconds << " секунд";

	//sqlite3_exec(db, "DELETE FROM my_urls;", NULL, NULL, NULL);
}




int main() {

	sqlite3* db;  // Хэндлер
	int connect_db = sqlite3_open("History", &db);  // открытие соединения с бд

	setlocale(LC_ALL, "Russian");
	int count_rows;
	std::cout << "Введите кол-во строк - ";
	std::cin >> count_rows;
	read_data(count_rows, db);


	//fill_table(db);


	sqlite3_close(db); // закрытие соединения с бд
	system("pause");

	return 0;
}
