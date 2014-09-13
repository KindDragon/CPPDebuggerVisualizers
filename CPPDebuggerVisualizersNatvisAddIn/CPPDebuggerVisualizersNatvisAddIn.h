// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the CPPDEBUGGERVISUALIZERSNATVISADDIN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// ADDIN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef CPPDEBUGGERVISUALIZERSNATVISADDIN_EXPORTS
#define ADDIN_API __declspec(dllexport)
#else
#define ADDIN_API __declspec(dllimport)
#endif

// This class is exported from the CPPDebuggerVisualizersNatvisAddIn.dll
class ADDIN_API CCPPDebuggerVisualizersNatvisAddIn {
public:
	CCPPDebuggerVisualizersNatvisAddIn(void);
	// TODO: add your methods here.
};

extern ADDIN_API int nCPPDebuggerVisualizersNatvisAddIn;

ADDIN_API int fnCPPDebuggerVisualizersNatvisAddIn(void);
