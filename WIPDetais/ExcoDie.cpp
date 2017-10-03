#include "StdAfx.h"

ExcoDie::ExcoDie(CString in_csID, CString in_csCurrentDate)
	:csID(in_csID), csCurrentDate(in_csCurrentDate)
{
	// get order date, customer id and customer name
	CString csQuery;
	if (!pRecordSet->IsEOF())
	{
		CString csValue;
		pRecordSet->GetFieldValue(L"DCODAT", csValue);
		csOrderDate = csValue.Trim();
		pRecordSet->GetFieldValue(L"DCBCUS", csValue);
		csCustID = csValue.Trim();
		pRecordSet->GetFieldValue(L"DCBNAM", csValue);
		csCustName = csValue.Trim();
	}
	pRecordSet->Close();
	// get ExcoPiece list, generate new ExcoPiece objects
	if (pRecordSet->IsOpen() && !pRecordSet->IsEOF())
	{
		CString csPartID;
		CString csPartDesc;
		pRecordSet->GetFieldValue(L"DNJOB", csPartID);
		pRecordSet->GetFieldValue(L"DNPART", csPartDesc);
		v_pPiece.push_back(new ExcoPiece(csPartID.Trim(), csPartDesc.Trim(), csCurrentDate));
	}
	pRecordSet->Close();
	csQuery.Format(L"select dnjob, dnpart from cmsdat.hjobh where dnord#='%s'", csID);
	if (pRecordSet->IsOpen() && !pRecordSet->IsEOF())
	{
		CString csPartID;
		CString csPartDesc;
		pRecordSet->GetFieldValue(L"DNJOB", csPartID);
		pRecordSet->GetFieldValue(L"DNPART", csPartDesc);
		v_pPiece.push_back(new ExcoPiece(csPartID.Trim(), csPartDesc.Trim(), csCurrentDate));
	}


ExcoDie::~ExcoDie()
{
	// delete all pieces
	for each (ExcoPiece* pPiece in v_pPiece)
	{
		delete pPiece;
	}
}