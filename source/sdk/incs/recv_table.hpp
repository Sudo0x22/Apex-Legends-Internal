#pragma once
#include<cassert>
class RecvTable;
class RecvProp;
class RecvProp
{
public:
	RecvProp();
	void InitArray(int elements, int stride);
	RecvTable* GetDataTable() const
	{
		return m_pDataTable;
	}
	RecvProp* GetArrayProp() const;
	int GetOffset() const {
		return m_Offset;
	}
public:
	const char* m_pVarName;
	int m_Flags;
	int m_StringBufferSize;
private:
	RecvTable* m_pDataTable;		// For RDT_DataTable.
	RecvProp* m_pArrayProp;
	int m_Offset;
	int m_Elements;
	int m_ElementsStride;
};

class RecvTable
{
public:
	typedef RecvProp PropType;
	RecvTable();
	RecvTable(RecvProp* pProps, int nProps, const char* pNetTableName);
	~RecvTable();
public:
	int GetNumProps() { return m_nProps; }
	inline RecvProp* GetProp(int i)
	{
		assert(i >= 0 && i < m_nProps);
		return &m_pProps[i];
	}
public:

	// Properties described in a table.
	RecvProp* m_pProps;
	int				m_nProps;

	// The decoder. NOTE: this covers each RecvTable AND all its children (ie: its children

	const char* m_pNetTableName;	// The name matched between client and server.


private:

	bool			m_bInitialized;
	bool			m_bInMainList;
};
