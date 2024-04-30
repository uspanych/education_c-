#include <iostream>
#include "sqlite3.h"
#include <string>



void read_data(int count, sqlite3* db) {
	sqlite3_stmt* pStatement;

	const char* sql = "SELECT id, url, title, last_visit_time FROM urls;";

	int execResult = sqlite3_prepare_v2(
		db,
		sql,
		-1,
		&pStatement,
		NULL
	);

	int k = 0;


	while (k <= count)
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

	}


}


void delete_table_row_by_id(int row_id, sqlite3* db) {
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
		std::cout << "Error in query!";
	}
}


int main() {

	sqlite3* db;
	int con_db = sqlite3_open("History", &db);
	setlocale(LC_ALL, "Russian");
	int count_rows;
	std::cout << "Write rows count - ";
	std::cin >> count_rows;
	read_data(count_rows, db);
	sqlite3_close(db);
	return 0;
}
