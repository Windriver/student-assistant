
class CUrlEncodeUnicode
{
private:
	static TCHAR toHex(BYTE val);
	static BYTE fromHex(TCHAR c);	//Hex TCHAR -> digit(int)
	static void toHexByte(BYTE val, LPTSTR buf);
	static void toHexWord(WORD val, LPTSTR buf);
	static BYTE fromHexByte(LPCTSTR ptr);
	static WORD fromHexWord(LPCTSTR ptr);
public:
	static bool Encode(LPCWSTR inurl, LPTSTR outurl, size_t size);
	static bool Decode(LPCTSTR inurl, LPWSTR outurl, size_t size);
};//class

