#include <bits/stdc++.h>
#include <string>
using namespace std;


class ASTNode{
public:
	virtual void visit(){}
	virtual void pb(ASTNode* a){}
};

class ASTvisitor{};

class VarName : public ASTNode{
public:
	string id;
	VarName(string value){
		id = value;
	}
	virtual void visit(){
		cout << " " << id << " ";
	}
};

class CompleteFileNodeOnlyBody : public ASTNode{
public:
	ASTNode* body;
	CompleteFileNodeOnlyBody(ASTNode* bodydata){
		body = bodydata;
	}
	virtual void visit(){
		// cout << "Global Declarations not present" << "\n";
		// cout << "body: ";
		body->visit();
		cout << "\n";
	}
};


class CompleteFileNodeWithGlobal : public ASTNode{
public:
	ASTNode* globaldecls, *body;
	// ASTNode;
	CompleteFileNodeWithGlobal(ASTNode* global_decls, ASTNode* bodydata){
		globaldecls = global_decls;
		body = bodydata;
	}
	virtual void visit(){
		cout << "Global Declarations present: ";
		globaldecls->visit();
		cout << "body: ";
		body->visit();
		cout << "\n";
	}
};


class GlobalDeclNode : public ASTNode{
public:
	vector<class ASTNode*> GDeclarations;
	void pb(ASTNode* a){
		GDeclarations.push_back(a);
	}
	GlobalDeclNode(){

	}
	virtual void visit(){
		cout << "Global Declarations: ";
		for(int i=0;i<GDeclarations.size();i++){
			cout << "GDeclarations[" << i << "] : ";
			GDeclarations[i]->visit();
			cout << "\n";
		}
	}
};

class GlobalDeclDef : public ASTNode{
public:
	ASTNode* Initi;
	ASTNode* exprone;
	ASTNode* exprtwo;
	GlobalDeclDef(ASTNode* VarName, ASTNode* expro=NULL, ASTNode* exprt=NULL){
		Initi = VarName;
		exprone = expro;
		exprtwo = exprt;

	}
	virtual void visit(){
		cout << "Global Defining : ";
		cout << "type - ";
		cout << "Defining(var name): ";
		Initi->visit();
		if(exprone!=NULL){
			cout << "[";
			exprone->visit();
			cout << "]";
		}
		if(exprtwo!=NULL){
			cout << "[";
			exprtwo->visit();
			cout << "]";
		}
		cout << "\n";
	}
};

class GlobalDeclDefAssign : public ASTNode{
public:
	ASTNode* Initi;
	string eqop;
	ASTNode* exprone;
	GlobalDeclDefAssign(ASTNode* initia, ASTNode* expro, string Eqoperator){
		Initi = initia;
		eqop = Eqoperator;
		exprone = expro;
	}
	virtual void visit(){
		cout << "Global Assigning : ";
		cout << "type";
		cout << "Defining(var name): ";
		Initi->visit();
		cout << " " << eqop << " ";
		exprone->visit();
	}
};

class GlobalDeclUse : public ASTNode{
public:
	ASTNode* var;
	string eqop;
	ASTNode* exprone;
	GlobalDeclUse(ASTNode* VarName, string Eqoperator, ASTNode* expro){
		var = VarName;
		eqop = Eqoperator;
		exprone = expro;
	}
	virtual void visit(){
		// cout << "Global Assigning : ";
		var->visit();
		cout << " " << eqop << " ";
		exprone->visit();
	}
};


class CharLitNode : public ASTNode{
public:
	char charLit;
	CharLitNode(char charVal){
		charLit = charVal;
	}
	virtual void visit(){
		cout  << charLit<< " (charLit)";
	}
};

class IntLitNode : public ASTNode{
public:
	int intLit;
	IntLitNode(int intVal){
		intLit = intVal;
	}
	virtual void visit(){
		cout << intLit << " (IntLit)";
	}
};


class BoolLitNode : public ASTNode{
public:
	string boolLit;
	BoolLitNode(string boolVal){
		boolLit = boolVal;
	}
	virtual void visit(){
		cout << boolLit<< " (BoolLit)";
	}
};





class BodyWithFunctionsNode : public ASTNode{
public:
	ASTNode* FuncList;
	ASTNode* MainFunc;
	BodyWithFunctionsNode(ASTNode* funclistdata, ASTNode* MainFuncdata){
		FuncList = funclistdata;
		MainFunc = MainFuncdata;
	}
	virtual void visit(){
		// cout << "Body contains Functions other than main: ";
		FuncList->visit();
		MainFunc->visit();
		// cout << "\n";
	}
};

class BodyOnlyMainNode : public ASTNode{
public:
	ASTNode* MainFunc;
	BodyOnlyMainNode(ASTNode* MainFuncdata){
		MainFunc = MainFuncdata;
	}
	virtual void visit(){
		cout << "Bosy contains only main function";
		MainFunc->visit();
	}
};

class AllFuncNode : public ASTNode{
public:
	vector<class ASTNode*> AllFuncList;
	void pb(ASTNode* a){
		AllFuncList.push_back(a);
	}
	AllFuncNode(){

	}
	virtual void visit(){
		// cout << "List of Functions: ";
		for(int i=0;i<AllFuncList.size();i++){
			// cout << "func no: " << i+1 << "\n";
			AllFuncList[i]->visit();
			cout << "\n";
		}
	}

};

class MainFuncNode : public ASTNode{
public:
	ASTNode* StatementList;
	ASTNode* Args;
	MainFuncNode(string namefunc, ASTNode* StatementListdata, ASTNode* Argsdata=NULL){
		StatementList = StatementListdata;
		Args = Argsdata;
	}
	virtual void visit(){
		cout << "def main( ";
		if(Args!=NULL){
			// cout << "Arguments: ";
			Args->visit();
			// cout << "\n";
		}
		cout << " ):" << "\n";
		// cout << "StatementList: ";
		StatementList->visit();
		cout << "\n";
	}
};

class FuncNode : public ASTNode{
public:
	ASTNode* FuncName, *StatementList, *ReturnStatement, *Args;
	FuncNode(ASTNode* FuncNamedata, ASTNode* StatementListdata,ASTNode* RtrnStmnt, ASTNode* Argsdata=NULL){
		FuncName = FuncNamedata;
		StatementList = StatementListdata;
		Args = Argsdata;
		ReturnStatement = RtrnStmnt;
	}
	virtual void visit(){
		cout << "def ";
		FuncName->visit();cout << "( ";
		if(Args!=NULL){
			// cout << "Arguments: ";
			Args->visit();
			cout << " ):";
			// cout << "\n";
		}
		// cout << "StatementList: ";
		StatementList->visit();
		cout << "\n";
		cout << ReturnStatement << "\n";
	}
};

class StatementNode : public ASTNode{
public:
	vector<class ASTNode*> StatementsList;
	void pb(ASTNode* a){
		StatementsList.push_back(a);
	}
	StatementNode(){

	}
	virtual void visit(){
		for(int i=0;i<StatementsList.size();i++){
			// cout << "statement no: " << i+1 << "\n";
			cout << "\n";
			StatementsList[i]->visit();
			// cout << "\n";
		}
	}
};

class VarDeclNode : public ASTNode{
public:
	string varType;
	ASTNode* loc;
	ASTNode* VarDecl;
	ASTNode* EndDecl;
	VarDeclNode(string type,ASTNode* loca,  ASTNode* Decl=NULL, ASTNode* EndDeclt=NULL){
		varType = type;
		VarDecl = Decl;
		loc = loca;
		EndDecl = EndDeclt;
	}
	virtual void visit(){
		cout << "here?" << varType << " ";
		loc->visit();
		if(VarDecl!=NULL){
			VarDecl->visit();
		}
		if(EndDecl!=NULL){
			EndDecl->visit();
		}
	}
};

class FuncCAllNode : public ASTNode{
public:
	ASTNode* namevar, *printableNode;
	// ASTNode;
	FuncCAllNode(ASTNode* namev, ASTNode* printable){
		printableNode = printable;
		namevar = namev;
	}
	virtual void visit(){
		// cout << "Function call: " << "\n";
		namevar->visit();
		cout << "(";
		printableNode->visit();
		cout << ");";
	}
};

class PrintNode : public ASTNode{
public:
	ASTNode* printableNode;
	PrintNode(ASTNode* printable){
		printableNode = printable;
	}
	virtual void visit(){
		cout << "print( ";
		printableNode->visit();
		cout << " );";
	}
};



class LiteralListNode : public ASTNode{
public:
	vector<class ASTNode*> LiteralsList;
	void pb(ASTNode* a){
		LiteralsList.push_back(a);
	}
	LiteralListNode(){

	}
	virtual void visit(){
		for(int i=LiteralsList.size()-1;i>=0;i--){
			// cout << "visiting " << i+1 << " literal";
			LiteralsList[i]->visit();
			if(i != 0)
				cout << ", ";
		}
	}
};


class VarListNode : public ASTNode{
public:
	vector<class ASTNode*> VarList;
	void pb(ASTNode* a){
		VarList.push_back(a);
	}
	VarListNode(){

	}
	virtual void visit(){
		for(int i=VarList.size()-1;i>=0;i--){
			// cout << "arg" << i+1 << "\n";
			cout << " ";
			VarList[i]->visit();
			if(i != 0)
				cout << ",";
		}
		// cout << "\n";
	}
};

class IFNode : public ASTNode{
public:
	ASTNode* exprone;
	ASTNode* StmntList;
	IFNode(ASTNode* expro, ASTNode* StatementsList){
		exprone = expro;
		StmntList = StatementsList;
	}
	virtual void visit(){
		cout << "IF (";
		exprone->visit();
		cout << " ) {";
		StmntList->visit();
		cout << "\n}";
		// cout << "\n";
	}
};

class IfElseNode : public ASTNode{
public:
	ASTNode* exprone, * StmntList, * ElifBlock, * ElseBlock;
	IfElseNode(ASTNode* expro, ASTNode* StatementsList, ASTNode* Elseblockdata, ASTNode* ElifBlockdata=NULL){
		exprone = expro;
		StmntList = StatementsList;
		ElifBlock = ElifBlockdata;
		ElseBlock = Elseblockdata;
	}
	virtual void visit(){
		cout << "IF(";
		exprone->visit();
		cout << " ){";
		StmntList->visit();
		cout << "\n}" << "\n";
		if(ElifBlock!=NULL){
			ElifBlock->visit();
		}
		cout << "\n";
		ElseBlock->visit();
		cout << "\n";
	}	
	
};

class NodeElse : public ASTNode{
public:
	ASTNode* StmntList;
	NodeElse(ASTNode* StatementsList){
		StmntList = StatementsList;
	}
	virtual void visit(){
		cout << "ELSE {";StmntList->visit();cout << "\n} \n";
	}
};

class ElifNodeQ : public ASTNode{
public:
	ASTNode* StmntList;
	ASTNode* exprone;
	ElifNodeQ(ASTNode* expro, ASTNode* StatementsLists){
		StmntList = StatementsLists;
		exprone = expro;
	}
	virtual void visit(){
		cout << "ELIF ( ";
		exprone->visit();
		cout << " ) {";
		StmntList->visit();
		cout << "\n}";
	}
};

class ElifNode : public ASTNode{
public:
	vector<class ASTNode*> listofelif;
	void pb(ASTNode* a){
		listofelif.push_back(a);
	}
	ElifNode(){

	}
	virtual void visit(){
		for(int i=0;i<listofelif.size();i++){
			// cout << "vising " << i+1 << "elif cond";
			listofelif[i]->visit();
			
		}
	}
};


class printablelist : public ASTNode{
public:
	vector<class ASTNode*> LiteralsList;
	void pb(ASTNode* a){
		LiteralsList.push_back(a);
	}
	printablelist(){

	}
	virtual void visit(){
		for(int i=0;i<LiteralsList.size();i++){
			// cout << "visiting " << i+1 << " literal";
			LiteralsList[i]->visit();
			if(i != 0)
				cout << ", ";
		}
	}
};


class ReturnNode : public ASTNode{
public:
	string returndef;
	ASTNode* exprone;
	ReturnNode(string returndefdata, ASTNode* expro=NULL){
		exprone = expro;
		returndef = returndefdata;
	}
	virtual void visit(){
		cout << returndef << " ";
		if(exprone!=NULL){
			exprone->visit();
		}
		cout << ";" << "\n";
	}
};

class EndNode : public ASTNode{
public:
	ASTNode* endStmnt;
	EndNode(ASTNode* enddef){
		endStmnt = enddef;
	}
	virtual void visit(){
		cout << "end(" << endStmnt << ")" << "\n";
	}
};

class MainEndNode : public ASTNode{
public:
	string endStmnt;
	MainEndNode(string enddef){
		endStmnt = enddef;
	}
	virtual void visit(){
		cout << "end(" << endStmnt << ")" << "\n";
	}
};

class ArgListNode : public ASTNode{
public:
	vector<class ASTNode*> ArgsList;
	void pb(ASTNode* a){
		ArgsList.push_back(a);
	}
	ArgListNode(){

	}
	virtual void visit(){
		for(int i=ArgsList.size()-1;i>=0;i--){
			// cout << "Args List: " << i+1 << " : ";
			ArgsList[i]->visit();
			if(i!=0)
				cout << ",";
		}
		// cout << "\n";
	}
};

class ArgListNodeQ : public ASTNode{
public:
	string varType;
	ASTNode* namevar;
	ArgListNodeQ(string typevar, ASTNode* nameVar){
		varType = typevar;
		namevar = nameVar;
	}
	virtual void visit(){
		cout << varType << " ";
		namevar->visit();
		// cout << " ;";
		// cout << "\n";
	}
};


class Initializer : public ASTNode{
public:
	ASTNode* namevar;
	string varType;
	Initializer(string typevar, ASTNode* nameVar){
		varType = typevar;
		namevar = nameVar;
	}
	virtual void visit(){
		cout << varType;
		cout  << " ";
		namevar->visit();
		cout << "\n";
	}
};


class ForNode : public ASTNode{
public:
	ASTNode* exprone;
	ASTNode* exprtwo;
	ASTNode* exprthr;
	ASTNode* StatementsList;
	ForNode(ASTNode* expro, ASTNode* exprt, ASTNode* exprth, ASTNode* StmntList){
		exprone = expro;
		exprtwo = exprt;
		exprthr = exprth;
		StatementsList = StmntList;
	}
	virtual void visit(){
		cout << "FOR (";
		exprone->visit();
		cout << " ; ";
		exprtwo->visit();
		cout << " ; ";
		exprthr->visit();
		cout << ") {";
		StatementsList->visit();
		cout << "\n}" << "\n";
	}
};

class exprASTnode : public ASTNode{
public:
	ASTNode* firstarg;
	exprASTnode(ASTNode* firstargdata){
		firstarg = firstargdata;
	}
	virtual void visit(){
		// cout<< " ";
		firstarg->visit();
		// cout << ";";
	}
};

class BinExpNode : public ASTNode{
public:
	ASTNode* exprone;
	string op;
	ASTNode* exprtwo;
	BinExpNode(ASTNode* expro, string ope, ASTNode* exprt){
		exprone = expro;
		op = ope;
		exprtwo = exprt;
	}
	virtual void visit(){
		exprone->visit();
		cout << " " << op << " ";
		exprtwo->visit();
		// cout << ";";
	}
};

class exprASTnodeB : public ASTNode{
public:
	string op1;
	ASTNode* exprone;
	string op2;
	exprASTnodeB(string expro,ASTNode* ope,string exprt){
		op1 = expro;
		exprone = ope;
		op2 = exprt;
	}
	virtual void visit(){
		cout << " " << op1 << " ";
		exprone->visit();
		cout << " " << op2 << " ";
		// exprtwo->visit();
		// cout << ";";
	}	
};

class NotExpNode : public ASTNode{
public:
	string op;
	ASTNode* exprone;
	NotExpNode(ASTNode* expro, string ope){
		op = ope;
		exprone = expro;
	}
	virtual void visit(){
		cout << op;
		exprone->visit();
		cout << "\n";
	}
};

class MethodCallNode : public ASTNode{
public:
	ASTNode* a;
	ASTNode* b;
	MethodCallNode(ASTNode* aa, ASTNode* bb=NULL){
		a = aa;
		b = bb;
	}
	virtual void visit(){
		cout << a << "(";
		if(b!=NULL){
			b->visit();
		}
		cout << ");" << "\n";
	}
};

class IOStmntNode : public ASTNode{
public:
	ASTNode* a;
	ASTNode* b;
	IOStmntNode(ASTNode* aa, ASTNode* bb){
		a = aa;
		b = bb;
	}
	virtual void visit(){
		// cout << "I/O Statement:" << "\n";
		// cout << a << "(" << b << ")" << "\n";
		cout << a << "( ";
		b->visit();
		cout << " );" << "\n";
	}
};

// class VarNameNodeQ : public ASTNode{
// public:
// 	ASTNode* a;
// 	ASTNode* b;
// 	ASTNode* c;
// 	VarNameNodeQ(ASTNode* aa, ASTNode* bb){
// 		a = aa;
// 		b = bb;
// 	}
// 	virtual void visit(){
// 		cout << "VarNameNode: ";
// 		a->visit();
// 		b->visit();
// 		// c->visit();
// 	}
// };

// class VarNameNode : public ASTNode{
// public:
// 	vector<class ASTNode*> vardecs;
// 	void pb(ASTNode* a){
// 		vardecs.push_back(a);
// 	}
// 	VarNameNode(){

// 	}
// 	virtual void visit(){
// 		for(int i=0;i<vardecs.size();i++){
// 			cout << "Args List: " << i+1 << " : ";
// 			vardecs[i]->visit();
// 			cout << ",";
// 		}
// 		cout << "\n";
// 	}
// };



// class DecEndNode : public ASTNode{
// public:
// 	string a;
// 	ASTNode* b;
// 	DecEndNode(string aa, ASTNode* bb=NULL){
// 		a = aa;
// 		b = bb;
// 	}
// 	virtual void visit(){
// 		if(a==","){
// 			cout << " " << a << " ";
// 		}
// 		if(b!=NULL){
// 			b->visit();
// 		}
// 	}
// };

class WhileNode : public ASTNode{
public:
	ASTNode* exprone;
	ASTNode* StatementList;
	WhileNode(ASTNode* a, ASTNode* b){
		exprone = a;
		StatementList = b;
	}
	virtual void visit(){
		cout << "WHILE (";
		exprone->visit();
		cout << ") {" << "\n";
		StatementList->visit();
		cout << "\n}" << "\n";
	}
};

class ParamListNode : public ASTNode{
public:
	vector<class ASTNode*> varnamelist;
	void pb(ASTNode* a){
		varnamelist.push_back(a);
	}
	ParamListNode(){

	}
	virtual void visit(){
		varnamelist[0]->visit();
		for(int i=1;i<varnamelist.size();i++){
			varnamelist[i]->visit();
			cout << "\n";
		}
		cout << "\n";
	}
};

class TernaryNode : public ASTNode{
public:
	ASTNode* a;
	ASTNode* b;
	ASTNode* c;
	TernaryNode(ASTNode* aa, ASTNode* bb, ASTNode* cc){
		a = aa;
		b = bb;
		c = cc;
	}
	virtual void visit(){
		a->visit();
		cout << " ? ";
		b->visit();
		cout << " : ";
		c->visit();
		cout << "\n";
	}
};

class ArrNodeOne : public ASTNode{
public:
	ASTNode* a;
	ASTNode* b;
	ASTNode* c;
	ArrNodeOne(ASTNode* aa, ASTNode* bb, ASTNode* cc=NULL){
		a = aa;
		b = bb;
		c = cc;
	}
	virtual void visit(){
		cout << a << " ";
		b->visit();
		if(c!=NULL){
			c->visit();
		cout << "\n";
		}
	}
};