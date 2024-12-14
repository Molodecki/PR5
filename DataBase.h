
#ifndef DataBaseH
#define DataBaseH
#include <System.Classes.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <vcl.h>
#include <map>
// Класс записи о машине
class DataRecord {
public:
	String ID;
	String Name;
	String Surname;
	String Patronymic;
	String CarNumber;
	String PhoneNumber;
	String CarModel;
	DataRecord(String id, String name, String surname, String patronymic, String carNumber, String phone, String carModel)
		: ID(id), Name(name), Surname(surname), Patronymic(patronymic), CarNumber(carNumber), PhoneNumber(phone), CarModel(carModel) {}

		 DataRecord()
		: ID(""), Name(""), Surname(""), Patronymic(""), CarNumber(""), PhoneNumber(""), CarModel("") {}
};
// Класс базы данных
class Database {
private:
	DataRecord* records;
	int recordCount;
	int MaxCount;

	void Size(int newSize);

public:
	Database(int initialCapacity = 10);
	~Database();
	void AddRecord(const DataRecord& record);
	DataRecord* GetRecordByID(const String& id);
	bool RemoveRecordByID(const String& id);
	DataRecord* GetAllRecords(int& count);
	String GetNextID();

	DataRecord* SearchRecords(const String& Value, int& count) {
		DataRecord* results = new DataRecord[recordCount];
		count = 0;
		for (int i = 0; i < recordCount; ++i) {
			if (records[i].Name.Pos(Value) ||
				records[i].Surname.Pos(Value) ||
				records[i].Patronymic.Pos(Value) ||
				records[i].CarNumber.Pos(Value) ||
				records[i].PhoneNumber.Pos(Value) ||
				records[i].CarModel.Pos(Value)) {
				results[count++] = records[i];
			}
		}
		return results;
	}

};

Database::~Database() {
	delete[] records;
}

// Иннециализация массива с начальной емкостью
	Database::Database(int initialCapacity)
	: recordCount(0), MaxCount(initialCapacity) {
	records = new DataRecord[MaxCount];
}

//Метод
void Database::AddRecord(const DataRecord& record) {
	if (recordCount >= MaxCount) {
		Size(MaxCount+1);
	}
	records[recordCount] = record;
	recordCount++;
}
 //--------------------------------------------------------------
 //Метод
void Database::Size(int newMaxCount) {
	DataRecord* newRecords = new DataRecord[newMaxCount];
	for (int i = 0; i < recordCount; ++i) {
		newRecords[i] = records[i];
	}
	delete[] records;
	records = newRecords;
	MaxCount = newMaxCount;
}

 //Поиск в массиве
DataRecord* Database::GetRecordByID(const String& id) {
	for (int i = 0; i < recordCount; ++i) {
		if (records[i].ID == id) {
			return &records[i];
		}
	}
	return 0;
}
//Удаление из массива
bool Database::RemoveRecordByID(const String& id) {
	for (int i = 0; i < recordCount; ++i) {
		if (records[i].ID == id) {
			for (int j = i; j < recordCount - 1; ++j) {
				records[j] = records[j + 1];
			}
			recordCount--;
			return true;
		}
	}
	return false;
}

DataRecord* Database::GetAllRecords(int& count) {
	count = recordCount;
	return records;
}

String Database::GetNextID() {
	int maxID = 0;
	for (int i = 0; i < recordCount; ++i) {
		int id = StrToIntDef(records[i].ID, 0);
		if (id > maxID) {
			maxID = id;
		}
	}
	return IntToStr(maxID + 1);
}


class TForm7 : public TForm {
__published:    // Компоненты, управляемые IDE
    TPanel *Panel1;
	TPanel *Panel2;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TTabSheet *TabSheet4;
	TEdit *Edit_Search;
    TButton *ChearchButton1;
    TListView *DataBase_Viev;
    TPanel *Panel3;
    TButton *Button2;
    TLabel *Label1;
	TLabel *Label2;
    TEdit *Edit_Name;
    TLabel *Label3;
    TEdit *Edit_Patronymic;
    TLabel *Label4;
    TEdit *Edit_CarNumber;
	TLabel *Label5;
    TEdit *Edit_PhoneNumber;
    TLabel *Label6;
    TEdit *Edit_CarModel;
    TEdit *Edit_Surname;
    TEdit *Edit_Delete;
	TButton *Button3;
    TLabel *Label7;
    TEdit *Edit_Change;
	TButton *Button4_Change;
	TPanel *Panel4_Old;
    TLabel *Label8;
	TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
	TEdit *Edit_OldName;
	TEdit *Edit_OldPatronymic;
	TEdit *Edit_OldCarNumber;
	TEdit *Edit_OldPhoneNumber;
	TEdit *Edit_OldCarModel;
	TEdit *Edit_OldSurName;
    TLabel *Label14;
	TEdit *Edit_ID;
	TPanel *Panel5_New;
    TLabel *Label15;
    TLabel *Label16;
    TLabel *Label17;
    TLabel *Label18;
	TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TEdit *Edit_NewName;
    TEdit *Edit_NewPatronymic;
    TEdit *Edit_NewCarNumber;
	TEdit *Edit_NewPhoneNumber;
    TEdit *Edit_NewCarModel;
    TEdit *Edit_NewSurname;
    TEdit *Edit_NewID;
	TButton *Button5_Confirm;
	TButton *Button1;
	TButton *Button4;
    void __fastcall Edit_SearchEnter(TObject *Sender);
	void __fastcall Edit_SearchExit(TObject *Sender);
    void __fastcall Edit_DeleteEnter(TObject *Sender);
    void __fastcall Edit_DeleteExit(TObject *Sender);
    void __fastcall Edit_ChangeEnter(TObject *Sender);
    void __fastcall Edit_ChangeExit(TObject *Sender);
    void __fastcall Button4_ChangeClick(TObject *Sender);
	void __fastcall ButtonChangeConfirmClick(TObject *Sender);
    void __fastcall Button_AddDataClick(TObject *Sender);
	void __fastcall ShowDataBaseView();
	void __fastcall Button_DeleteClick(TObject *Sender);
	void __fastcall ChearchButton1Click(TObject *Sender);
	void __fastcall Button_SortingUp_Click(TObject *Sender);
	void __fastcall Button_SortingDown_Click(TObject *Sender);
private:
	Database database;
	void __fastcall SortDatabase(bool ascending);
public:
	__fastcall TForm7(TComponent* Owner);
};
#endif
