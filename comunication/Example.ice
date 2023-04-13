module ExampleModule
{

	enum Enumeration { value1, value2, value3 };

	struct RowData
	{
		int 		id;
		string 		stringData;
		Enumeration enumData;
		double 		doubleData;
		bool		boolData;
		string 		dateTimeData;
	}

	sequence<RowData> AllRowData;

    interface ExampleInterface
    {
        void addRowData(RowData data);
		AllRowData getRowsData();
		void changeStringData(int id, string newStringData);
		void changeEnumData(int id, Enumeration newEnumData);
		void changeDoubleData(int id, double newDoubleData);
		void changeBoolData(int id, bool newBoolData);
		void changeDateTimeData(int id, string newDateTimeData);
		void deleteRowData(int id);
    }
}