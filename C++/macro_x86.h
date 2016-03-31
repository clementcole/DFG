#ifndef MACRO_X86_H
#define MACRO_X86_H
	

//Primary opcodes po
#define ADD 	0x0000
#define OR  	0x0001
#define ADC 	0x0010
#define SBB     0x0018
#define AND 	0x0020
#define SUB		0x0028
#define XOR		0x0030
#define CMP		0x0038
#define REX     0x0040 
#define REX_X 	0x0041
#define REX_XB	0x0043
#define PUSH	0x0050
#define POP 	0x0058
#define MOVSXD  0x0063

//Secondary Opcodes so
//Opcode fields flds
//Prefix pf

	static symstr macro_X86[] = {
		{"ADD", ADD},
		{"OR" , OR},
		{"ADC" ,ADC},
		{"SBB" ,SBB},
		{"AND" ,AND},
		{"SUB", SUB},
		{"XOR", XOR},
		{"CMP", CMP},
		{"REX", REX},
		{"REX.B", REX_B},
		{"REX.XB", REX_XB},
		{"PUSH", PUSH},
		{"POP", POP},
		{"MOVSXD", MOVSXD}
		};
		//WEbsite : ref.x86asm.net/coder64.html#x02
#endif