// Copyright 2009 proDOOMman
// Distributed under the terms of the GNU General Public License v2

#include "hightlighter.h"

#include <QDebug>

highlighter::highlighter(QTextDocument *parent, settingsClass *sc)
     : QSyntaxHighlighter(parent)
 {
    set = sc;
     QStringList proc, number, string, identifer, comment;
     //виды подсветки:
     hl << "identifer"
        << "number"
        << "masmOption"
        << "masmType"
        << "masmOperator"
        << "masmDirective"
        << "masmRegister"
        << "masmOpcode"
        << "masmOpFloat"
        << "proc"
        << "string"
        << "comment";

     foreach(QString name, hl)
        containerFormat[name] = set->getFontFormat(name);

     container["identifer"] << "[a-zA-Z\\_][a-zA-Z0-9\\_]*";
     container["proc"] << "^\\s*[a-zA-Z\\_][a-zA-Z0-9\\_]*:";
     container["number"] << "[-+]?\\d+[dt]?"                         //dec
             << "[-+]?[0-1]+[by]"                         //bin
             << "[-+]?[0-7]+[oq]"                         //oct
             << "[-+]?[0-9,a-f,A-F]+h"                    //hex
             << "[-+]?[0-9]+r"                            //floatRaw
             << "[-+]?\\d+\\.(\\d*(E[-+]?\\d+)?)?";       //float
     container["comment"] << ";.*";
     container["string"] << "\'.*\'" << "\".*\"";
     container["masmOption"] << "TINY" << "SMALL" << "COMPACT" << "MEDIUM" << "LARGE" << "HUGE"
                            << "NEARSTACK" << "FARSTACK"
                            << "PUBLIC" << "PRIVATE" << "STACK" << "COMMON" << "MEMORY" << "AT"
                            << "BYTE" << "WORD" << "DWORD" << "PARA" << "PAGE"
                            << "USE16" << "USE32" << "FLAT"
                            << "INFO" << "READ" << "WRITE" << "EXECUTE" << "SHARED"
                            << "NOPAGE" << "NOCACHE" << "DISCARD"
                            << "READONLY" << "USES" << "FRAME"
                            << "CASEMAP" << "DOTNAME" << "NODOTNAME" << "EMULATOR"
                            << "NOEMULATOR" << "EPILOGUE" << "EXPR16" << "EXPR32"
                            << "LANGUAGE" << "LJMP" << "NOLJMP" << "M510" << "NOM510"
                            << "NOKEYWORD" << "NOSIGNEXTEND" << "OFFSET"
                            << "OLDMACROS" << "NOOLDMACROS" << "OLDSTRUCTS"
                            << "NOOLDSTRUCTS" << "PROC" << "PROLOGUE" << "READONLY"
                            << "NOREADONLY" << "SCOPED" << "NOSCOPED" << "SEGMENT"
                            << "SETIF2"
                            << "ABS" << "ALL" << "ASSUMES" << "CPU" << "ERROR" << "EXPORT"
                            << "FORCEFRAME" << "LISTING" << "LOADDS" << "NONE"
                            << "NONUNIQUE" << "NOTHING" << "OS_DOS" << "RADIX" << "REQ"
                            //match
                            << "ALIGN([0-9]+)";
     container["masmType"]  << "STDCALL" << "SYSCALL"/* << "C"*/ << "BASIC" << "FORTRAN" << "PASCAL"
                            << "PTR" << "NEAR" << "FAR" << "NEAR16" << "FAR16" << "NEAR32" << "FAR32"
                            << "REAL4" << "REAL8" << "REAL10" << "BYTE" << "SBYTE" << "TBYTE"
                            << "WORD" << "DWORD" << "QWORD" << "FWORD" << "SWORD" << "SDWORD";
     container["masmOperator"]  << "AND" << "NOT" << "OR" << "SHL" << "SHR" << "XOR" << "MOD" << "DUP"
                                << "EQ" << "GE" << "GT" << "LE" << "LT" << "NE"
                                << "LROFFSET" << "SEG" << "LENGTH" << "LENGTHOF" << "SIZE" << "SIZEOF"
                                << "CODEPTR" << "DATAPTR" << "FAR" << "NEAR" << "SHORT" << "THIS" << "TYPE"
                                << "HIGH" << "HIGHWORD" << "LOW" << "LOWWORD" << "OPATTR" << "MASK" << "WIDTH"
                                << "OFFSET(\\sFLAT:)?" << "\\.TYPE" << "CARRY\\?" << "OVERFLOW\\"
                                << "PARITY\\?" << "SIGN\\?" << "ZERO\\?";
     container["masmDirective"] << "ALIAS" << "ASSUME" << "CATSTR" << "COMM" << "DB" << "DD" << "DF" << "DOSSEG" << "DQ" << "DT"
                                << "DW" << "ECHO" << "ELSE" << "ELSEIF" << "ELSEIF1" << "ELSEIF2" << "ELSEIFB"
                                << "ELSEIFDEF" << "ELSEIFDIF" << "ELSEIFDIFI" << "ELSEIFE"
                                << "ELSEIFIDN" << "ELSEIFIDNI" << "ELSEIFNB" << "ELSEIFNDEF" << "END"
                                << "ENDIF" << "ENDM" << "ENDP" << "ENDS" << "EQU" << "EVEN" << "EXITM" << "EXTERN"
                                << "EXTERNDEF" << "EXTRN" << "FOR" << "FORC" << "GOTO" << "GROUP" << "IF" << "IF1" << "IF2"
                                << "IFB" << "IFDEF" << "IFDIF" << "IFDIFI" << "IFE" << "IFIDN" << "IFIDNI" << "IFNB"
                                << "IFNDEF" << "INCLUDE" << "INCLUDELIB" << "INSTR" << "INVOKE" << "IRP"
                                << "IRPC" << "LABEL" << "LOCAL" << "MACRO" << "NAME" << "OPTION" << "ORG" << "PAGE"
                                << "POPCONTEXT" << "PROC" << "PROTO" << "PUBLIC" << "PURGE" << "PUSHCONTEXT"
                                << "RECORD" << "REPEAT" << "REPT" << "SEGMENT" << "SIZESTR" << "STRUC"
                                << "STRUCT" << "SUBSTR" << "SUBTITLE" << "SUBTTL" << "TEXTEQU" << "TITLE"
                                << "TYPEDEF" << "UNION" << "WHILE"
                                //match
                                << "\\.8086" << "\\.8087" << "\\.NO87" << "\\.186" << "\\.286"
                                << "\\.286C" << "\\.286P" << "\\.287" << "\\.386" << "\\.386C"
                                << "\\.386P" << "\\.387" << "\\.486" << "\\.486P" << "\\.586"
                                << "\\.586P" << "\\.686" << "\\.686P" << "\\.K3D" << "\\.MMX"
                                << "\\.XMM" << "\\.ALPHA" << "\\.DOSSEG" << "\\.SEQ" << "\\.CODE"
                                << "\\.CONST" << "\\.DATA" << "\\.DATA?" << "\\.EXIT" << "\\.FARDATA"
                                << "\\.FARDATA?" << "\\.MODEL" << "\\.STACK" << "\\.STARTUP" << "\\.IF"
                                << "\\.ELSE" << "\\.ELSEIF" << "\\.ENDIF" << "\\.REPEAT" << "\\.UNTIL"
                                << "\\.UNTILCXZ" << "\\.WHILE" << "\\.ENDW" << "\\.BREAK" << "\\.CONTINUE"
                                << "\\.ERR" << "\\.ERR1" << "\\.ERR2" << "\\.ERRB" << "\\.ERRDEF"
                                << "\\.ERRDIF" << "\\.ERRDIFI" << "\\.ERRE" << "\\.ERRIDN" << "\\.ERRIDNI"
                                << "\\.ERRNB" << "\\.ERRNDEF" << "\\.ERRNZ" << "\\.LALL" << "\\.SALL"
                                << "\\.XALL" << "\\.LFCOND" << "\\.SFCOND" << "\\.TFCOND" << "\\.CREF"
                                << "\\.NOCREF" << "\\.XCREF" << "\\.LIST" << "\\.NOLIST" << "\\.XLIST"
                                << "\\.LISTALL" << "\\.LISTIF" << "\\.NOLISTIF" << "\\.LISTMACRO"
                                << "\\.NOLISTMACRO"
                                << "\\.LISTMACROALL" << "\\.FPO" << "\\.RADIX" << "\\.SAFESEH" << "\\%OUT"
                                << "ALIGN";
     container["masmRegister"]  << "AX" << "BX" << "CX" << "DX" << "SI" << "DI" << "BP" << "SP"
                                << "CS" << "DS" << "SS" << "ES" << "FS" << "GS"
                                << "AH" << "BH" << "CH" << "DH" << "AL" << "BL" << "CL" << "DL"
                                << "EAX" << "EBX" << "ECX" << "EDX" << "ESI" << "EDI" << "EBP" << "ESP"
                                << "CR0" << "CR2" << "CR3" << "CR4"
                                << "DR0" << "DR1" << "DR2" << "DR3" << "DR6" << "DR7"
                                << "TR3" << "TR4" << "TR5" << "TR6" << "TR7"
                                //match
                                << "ST([0-7])";
     container["masmOpcode"]
                                //Instruction prefixes
                                << "LOCK" << "REP" << "REPE" << "REPNE" << "REPNZ" << "REPZ"
                                //8086/8088 opcodes
                                << "AAA" << "AAD" << "AAM" << "AAS" << "ADC" << "ADD" << "AND" << "CALL" << "CBW" << "CLC" << "CLD"
                                << "CLI" << "CMC" << "CMP" << "CMPS" << "CMPSB" << "CMPSW" << "CWD" << "DAA" << "DAS" << "DEC"
                                << "DIV" << "ESC" << "HLT" << "IDIV" << "IMUL" << "IN" << "INC" << "INT" << "INTO" << "IRET"
                                << "JCXZ" << "JMP" << "LAHF" << "LDS" << "LEA" << "LES" << "LODS" << "LODSB" << "LODSW"
                                << "LOOP" << "LOOPE" << "LOOPEW" << "LOOPNE" << "LOOPNEW" << "LOOPNZ"
                                << "LOOPNZW" << "LOOPW" << "LOOPZ" << "LOOPZW" << "MOV" << "MOVS" << "MOVSB"
                                << "MOVSW" << "MUL" << "NEG" << "NOP" << "NOT" << "OR" << "OUT" << "POP" << "POPF" << "PUSH"
                                << "PUSHF" << "RCL" << "RCR" << "RET" << "RETF" << "RETN" << "ROL" << "ROR" << "SAHF" << "SAL"
                                << "SAR" << "SBB" << "SCAS" << "SCASB" << "SCASW" << "SHL" << "SHR" << "STC" << "STD" << "STI"
                                << "STOS" << "STOSB" << "STOSW" << "SUB" << "TEST" << "WAIT" << "XCHG" << "XLAT" << "XLATB"
                                << "XOR"
                                //match
                                << "J(P[EO]|(N?([ABGL]E?|[CEOPSZ])))\\b"
                                //80186 opcodes
                                << "BOUND" << "ENTER" << "INS" << "INSB" << "INSW" << "LEAVE" << "OUTS" << "OUTSB"
                                << "OUTSW" << "POPA" << "PUSHA" << "PUSHW"
                                //80286 opcodes
                                << "ARPL" << "LAR" << "LSL" << "SGDT" << "SIDT" << "SLDT" << "SMSW" << "STR" << "VERR" << "VERW"
                                //80286/80386 privileged opcodes
                                << "CLTS" << "LGDT" << "LIDT" << "LLDT" << "LMSW" << "LTR"
                                //80386 opcodes
                                << "BSF" << "BSR" << "BT" << "BTC" << "BTR" << "BTS" << "CDQ" << "CMPSD" << "CWDE" << "INSD"
                                << "IRETD" << "IRETDF" << "IRETF" << "JECXZ" << "LFS" << "LGS" << "LODSD" << "LOOPD"
                                << "LOOPED" << "LOOPNED" << "LOOPNZD" << "LOOPZD" << "LSS" << "MOVSD" << "MOVSX"
                                << "MOVZX" << "OUTSD" << "POPAD" << "POPFD" << "PUSHAD" << "PUSHD" << "PUSHFD"
                                << "SCASD" << "SHLD" << "SHRD" << "STOSD"
                                //match
                                << "SET(P[EO]|(N?([ABGL]E?|[CEOPSZ])))\\b"
                                //80486 opcodes
                                << "BSWAP" << "CMPXCHG" << "INVD" << "INVLPG" << "WBINVD" << "XADD";
     container["masmOpFloat"]
                                //Floating-point opcodes as of 487
                                << "F2XM1" << "FABS" << "FADD" << "FADDP" << "FBLD" << "FBSTP" << "FCHS" << "FCLEX"
                                << "FNCLEX" << "FCOM" << "FCOMP" << "FCOMPP" << "FCOS" << "FDECSTP" << "FDISI"
                                << "FNDISI" << "FDIV" << "FDIVP" << "FDIVR" << "FDIVRP" << "FENI" << "FNENI"
                                << "FFREE" << "FIADD" << "FICOM" << "FICOMP" << "FIDIV" << "FIDIVR" << "FILD"
                                << "FIMUL" << "FINCSTP" << "FINIT" << "FNINIT" << "FIST" << "FISTP" << "FISUB"
                                << "FISUBR" << "FLD" << "FLDCW" << "FLDENV" << "FLDLG2" << "FLDLN2" << "FLDL2E"
                                << "FLDL2T" << "FLDPI" << "FLDZ" << "FLD1" << "FMUL" << "FMULP" << "FNOP" << "FPATAN"
                                << "FPREM" << "FPREM1" << "FPTAN" << "FRNDINT" << "FRSTOR" << "FSAVE" << "FNSAVE"
                                << "FSCALE" << "FSETPM" << "FSIN" << "FSINCOS" << "FSQRT" << "FST" << "FSTCW"
                                << "FNSTCW" << "FSTENV" << "FNSTENV" << "FSTP" << "FSTSW" << "FNSTSW" << "FSUB"
                                << "FSUBP" << "FSUBR" << "FSUBRP" << "FTST" << "FUCOM" << "FUCOMP" << "FUCOMPP"
                                << "FWAIT" << "FXAM" << "FXCH" << "FXTRACT" << "FYL2X" << "FYL2XP1"
                                //Floating-point opcodes in Pentium and later processors
                                << "FCMOVE" << "FCMOVNE" << "FCMOVB" << "FCMOVBE" << "FCMOVNB" << "FCMOVNBE"
                                << "FCMOVU" << "FCMOVNU" << "FCOMI" << "FUCOMI" << "FCOMIP" << "FUCOMIP"
                                << "FXSAVE" << "FXRSTOR";
     container["masmOpcode"]
                                //MMX opcodes (Pentium w/ MMX, Pentium II, and later)
                                << "MOVD" << "MOVQ" << "PACKSSWB" << "PACKSSDW" << "PACKUSWB"
                                << "PUNPCKHBW" << "PUNPCKHWD" << "PUNPCKHDQ"
                                << "PUNPCKLBW" << "PUNPCKLWD" << "PUNPCKLDQ"
                                << "PADDB" << "PADDW" << "PADDD" << "PADDSB" << "PADDSW" << "PADDUSB" << "PADDUSW"
                                << "PSUBB" << "PSUBW" << "PSUBD" << "PSUBSB" << "PSUBSW" << "PSUBUSB" << "PSUBUSW"
                                << "PMULHW" << "PMULLW" << "PMADDWD"
                                << "PCMPEQB" << "PCMPEQW" << "PCMPEQD" << "PCMPGTB" << "PCMPGTW" << "PCMPGTD"
                                << "PAND" << "PANDN" << "POR" << "PXOR"
                                << "PSLLW" << "PSLLD" << "PSLLQ" << "PSRLW" << "PSRLD" << "PSRLQ" << "PSRAW" << "PSRAD"
                                << "EMMS"
                                //SSE opcodes (Pentium III and later)
                                << "MOVAPS" << "MOVUPS" << "MOVHPS" << "MOVHLPS" << "MOVLPS" << "MOVLHPS"
                                << "MOVMSKPS" << "MOVSS"
                                << "ADDPS" << "ADDSS" << "SUBPS" << "SUBSS" << "MULPS" << "MULSS" << "DIVPS" << "DIVSS"
                                << "RCPPS" << "RCPSS" << "SQRTPS" << "SQRTSS" << "RSQRTPS" << "RSQRTSS"
                                << "MAXPS" << "MAXSS" << "MINPS" << "MINSS"
                                << "CMPPS" << "CMPSS" << "COMISS" << "UCOMISS"
                                << "ANDPS" << "ANDNPS" << "ORPS" << "XORPS"
                                << "SHUFPS" << "UNPCKHPS" << "UNPCKLPS"
                                << "CVTPI2PS" << "CVTSI2SS" << "CVTPS2PI" << "CVTTPS2PI"
                                << "CVTSS2SI" << "CVTTSS2SI"
                                << "LDMXCSR" << "STMXCSR"
                                << "PAVGB" << "PAVGW" << "PEXTRW" << "PINSRW" << "PMAXUB" << "PMAXSW"
                                << "PMINUB" << "PMINSW" << "PMOVMSKB" << "PMULHUW" << "PSADBW" << "PSHUFW"
                                << "MASKMOVQ" << "MOVNTQ" << "MOVNTPS" << "SFENCE"
                                << "PREFETCHT0" << "PREFETCHT1" << "PREFETCHT2" << "PREFETCHNTA"
                                //SSE2 opcodes (Pentium 4 and later)
                                << "MOVAPD" << "MOVUPD" << "MOVHPD" << "MOVLPD" << "MOVMSKPD" << "MOVSD"
                                << "ADDPD" << "ADDSD" << "SUBPD" << "SUBSD" << "MULPD" << "MULSD" << "DIVPD" << "DIVSD"
                                << "SQRTPD" << "SQRTSD" << "MAXPD" << "MAXSD" << "MINPD" << "MINSD"
                                << "ANDPD" << "ANDNPD" << "ORPD" << "XORPD"
                                << "CMPPD" << "CMPSD" << "COMISD" << "UCOMISD"
                                << "SHUFPD" << "UNPCKHPD" << "UNPCKLPD"
                                << "CVTPD2PI" << "CVTTPD2PI" << "CVTPI2PD" << "CVTPD2DQ"
                                << "CVTTPD2DQ" << "CVTDQ2PD" << "CVTPS2PD" << "CVTPD2PS"
                                << "CVTSS2SD" << "CVTSD2SS" << "CVTSD2SI" << "CVTTSD2SI" << "CVTSI2SD"
                                << "CVTDQ2PS" << "CVTPS2DQ" << "CVTTPS2DQ"
                                << "MOVDQA" << "MOVDQU" << "MOVQ2DQ" << "MOVDQ2Q" << "PMULUDQ"
                                << "PADDQ" << "PSUBQ" << "PSHUFLW" << "PSHUFHW" << "PSHUFD"
                                << "PSLLDQ" << "PSRLDQ" << "PUNPCKHQDQ" << "PUNPCKLQDQ"
                                << "CLFLUSH" << "LFENCE" << "MFENCE" << "PAUSE" << "MASKMOVDQU"
                                << "MOVNTPD" << "MOVNTDQ" << "MOVNTI"
                                //SSE3 opcodes (Pentium 4 w/ Hyper-Threading and later)
                                << "FISTTP" << "LDDQU" << "ADDSUBPS" << "ADDSUBPD"
                                << "HADDPS" << "HSUBPS" << "HADDPD" << "HSUBPD"
                                << "MOVSHDUP" << "MOVSLDUP" << "MOVDDUP" << "MONITOR" << "MWAIT"
                                //Other opcodes in Pentium and later processors
                                << "CMPXCHG8B" << "CPUID" << "UD2"
                                << "RSM" << "RDMSR" << "WRMSR" << "RDPMC" << "RDTSC" << "SYSENTER" << "SYSEXIT"
                                //match
                                << "CMOV(P[EO]|(N?([ABGL]E?|[CEOPSZ])))";
     initRules();
 }

void highlighter::initRules()
{
    highlightingRules.clear();
     HighlightingRule rule;
     QStringList special;
     special << "identifer" << "proc" << "comment" << "string";
     foreach(QString st, hl)
     {
         rule.format = containerFormat[st];
         if(special.contains(st))
            foreach(QString pat, container[st])
                {
                    rule.pattern = QRegExp(pat,Qt::CaseInsensitive);
                    highlightingRules.append(rule);
                }
         else
            foreach(QString pat, container[st])
                {
                    if(pat.indexOf("\\.")==0)
                        rule.pattern = QRegExp("^\\s*"+pat+"\\b",Qt::CaseInsensitive);
                    else
                        rule.pattern = QRegExp("\\b"+pat+"\\b",Qt::CaseInsensitive);
                    highlightingRules.append(rule);
                }
     }
}

 void highlighter::highlightBlock(const QString &text)
 {
     if(set->isChanged())
     {
         foreach(QString name, hl)
            containerFormat[name] = set->getFontFormat(name);
         initRules();
     }
     foreach (HighlightingRule rule, highlightingRules) {
         int index = text.indexOf(rule.pattern);
         while (index >= 0) {
             int length = rule.pattern.matchedLength();
             setFormat(index, length, rule.format);
             index = text.indexOf(rule.pattern, index + length);
         }
     }
 }
