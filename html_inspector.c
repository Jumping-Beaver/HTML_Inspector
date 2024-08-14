#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/*****************************************************************************/
/* Helpers need by both `HtmlDocument` and `Selector` */

static const char *ENTITIES[1 + (unsigned char) -1] = {
    ['A'] =
    "&AElig;Æ&AMP;&&Aacute;Á&Abreve;Ă&Acirc;Â&Acy;А&Afr;𝔄&Agrave;À&Alpha;Α&Amacr;Ā&And;⩓&Aogon;Ą"
    "&Aopf;𝔸&ApplyFunction;⁡&Aring;Å&Ascr;𝒜&Assign;≔&Atilde;Ã&Auml;Ä",
    ['B'] =
    "&Backslash;∖&Barv;⫧&Barwed;⌆&Bcy;Б&Because;∵&Bernoullis;ℬ&Beta;Β&Bfr;𝔅&Bopf;𝔹&Breve;˘"
    "&Bscr;ℬ&Bumpeq;≎",
    ['C'] =
    "&CHcy;Ч&COPY;©&Cacute;Ć&Cap;⋒&CapitalDifferentialD;ⅅ&Cayleys;ℭ&Ccaron;Č&Ccedil;Ç&Ccirc;Ĉ"
    "&Cconint;∰&Cdot;Ċ&Cedilla;¸&CenterDot;·&Cfr;ℭ&Chi;Χ&CircleDot;⊙&CircleMinus;⊖&CirclePlus;⊕"
    "&CircleTimes;⊗&ClockwiseContourIntegral;∲&CloseCurlyDoubleQuote;”&CloseCurlyQuote;’&Colon;∷"
    "&Colone;⩴&Congruent;≡&Conint;∯&ContourIntegral;∮&Copf;ℂ&Coproduct;∐&CounterClockwiseContourIntegral;∳"
    "&Cross;⨯&Cscr;𝒞&Cup;⋓&CupCap;≍",
    ['D'] =
    "&DD;ⅅ&DDotrahd;⤑&DJcy;Ђ&DScy;Ѕ&DZcy;Џ&Dagger;‡&Darr;↡&Dashv;⫤&Dcaron;Ď&Dcy;Д&Del;∇&Delta;Δ"
    "&Dfr;𝔇&DiacriticalAcute;´&DiacriticalDot;˙&DiacriticalDoubleAcute;˝&DiacriticalGrave;`&DiacriticalTilde;˜"
    "&Diamond;⋄&DifferentialD;ⅆ&Dopf;𝔻&Dot;¨&DotDot;⃜&DotEqual;≐&DoubleContourIntegral;∯&DoubleDot;¨"
    "&DoubleDownArrow;⇓&DoubleLeftArrow;⇐&DoubleLeftRightArrow;⇔&DoubleLeftTee;⫤&DoubleLongLeftArrow;⟸"
    "&DoubleLongLeftRightArrow;⟺&DoubleLongRightArrow;⟹&DoubleRightArrow;⇒&DoubleRightTee;⊨&DoubleUpArrow;⇑"
    "&DoubleUpDownArrow;⇕&DoubleVerticalBar;∥&DownArrow;↓&DownArrowBar;⤓&DownArrowUpArrow;⇵"
    "&DownBreve;̑&DownLeftRightVector;⥐&DownLeftTeeVector;⥞&DownLeftVector;↽&DownLeftVectorBar;⥖"
    "&DownRightTeeVector;⥟&DownRightVector;⇁&DownRightVectorBar;⥗&DownTee;⊤&DownTeeArrow;↧&Downarrow;⇓"
    "&Dscr;𝒟&Dstrok;Đ",
    ['E'] =
    "&ENG;Ŋ&ETH;Ð&Eacute;É&Ecaron;Ě&Ecirc;Ê&Ecy;Э&Edot;Ė&Efr;𝔈&Egrave;È&Element;∈&Emacr;Ē&EmptySmallSquare;◻"
    "&EmptyVerySmallSquare;▫&Eogon;Ę&Eopf;𝔼&Epsilon;Ε&Equal;⩵&EqualTilde;≂&Equilibrium;⇌&Escr;ℰ"
    "&Esim;⩳&Eta;Η&Euml;Ë&Exists;∃&ExponentialE;ⅇ",
    ['F'] =
    "&Fcy;Ф&Ffr;𝔉&FilledSmallSquare;◼&FilledVerySmallSquare;▪&Fopf;𝔽&ForAll;∀&Fouriertrf;ℱ"
    "&Fscr;ℱ",
    ['G'] =
    "&GJcy;Ѓ&GT;>&Gamma;Γ&Gammad;Ϝ&Gbreve;Ğ&Gcedil;Ģ&Gcirc;Ĝ&Gcy;Г&Gdot;Ġ&Gfr;𝔊&Gg;⋙&Gopf;𝔾&GreaterEqual;≥"
    "&GreaterEqualLess;⋛&GreaterFullEqual;≧&GreaterGreater;⪢&GreaterLess;≷&GreaterSlantEqual;⩾"
    "&GreaterTilde;≳&Gscr;𝒢&Gt;≫",
    ['H'] =
    "&HARDcy;Ъ&Hacek;ˇ&Hat;^&Hcirc;Ĥ&Hfr;ℌ&HilbertSpace;ℋ&Hopf;ℍ&HorizontalLine;─&Hscr;ℋ&Hstrok;Ħ"
    "&HumpDownHump;≎&HumpEqual;≏",
    ['I'] =
    "&IEcy;Е&IJlig;Ĳ&IOcy;Ё&Iacute;Í&Icirc;Î&Icy;И&Idot;İ&Ifr;ℑ&Igrave;Ì&Im;ℑ&Imacr;Ī&ImaginaryI;ⅈ"
    "&Implies;⇒&Int;∬&Integral;∫&Intersection;⋂&InvisibleComma;⁣&InvisibleTimes;⁢&Iogon;Į&Iopf;𝕀"
    "&Iota;Ι&Iscr;ℐ&Itilde;Ĩ&Iukcy;І&Iuml;Ï",
    ['J'] =
    "&Jcirc;Ĵ&Jcy;Й&Jfr;𝔍&Jopf;𝕁&Jscr;𝒥&Jsercy;Ј&Jukcy;Є",
    ['K'] =
    "&KHcy;Х&KJcy;Ќ&Kappa;Κ&Kcedil;Ķ&Kcy;К&Kfr;𝔎&Kopf;𝕂&Kscr;𝒦",
    ['L'] =
    "&LJcy;Љ&LT;<&Lacute;Ĺ&Lambda;Λ&Lang;⟪&Laplacetrf;ℒ&Larr;↞&Lcaron;Ľ&Lcedil;Ļ&Lcy;Л&LeftAngleBracket;⟨"
    "&LeftArrow;←&LeftArrowBar;⇤&LeftArrowRightArrow;⇆&LeftCeiling;⌈&LeftDoubleBracket;⟦&LeftDownTeeVector;⥡"
    "&LeftDownVector;⇃&LeftDownVectorBar;⥙&LeftFloor;⌊&LeftRightArrow;↔&LeftRightVector;⥎&LeftTee;⊣"
    "&LeftTeeArrow;↤&LeftTeeVector;⥚&LeftTriangle;⊲&LeftTriangleBar;⧏&LeftTriangleEqual;⊴&LeftUpDownVector;⥑"
    "&LeftUpTeeVector;⥠&LeftUpVector;↿&LeftUpVectorBar;⥘&LeftVector;↼&LeftVectorBar;⥒&Leftarrow;⇐"
    "&Leftrightarrow;⇔&LessEqualGreater;⋚&LessFullEqual;≦&LessGreater;≶&LessLess;⪡&LessSlantEqual;⩽"
    "&LessTilde;≲&Lfr;𝔏&Ll;⋘&Lleftarrow;⇚&Lmidot;Ŀ&LongLeftArrow;⟵&LongLeftRightArrow;⟷&LongRightArrow;⟶"
    "&Longleftarrow;⟸&Longleftrightarrow;⟺&Longrightarrow;⟹&Lopf;𝕃&LowerLeftArrow;↙&LowerRightArrow;↘"
    "&Lscr;ℒ&Lsh;↰&Lstrok;Ł&Lt;≪",
    ['M'] =
    "&Map;⤅&Mcy;М&MediumSpace; &Mellintrf;ℳ&Mfr;𝔐&MinusPlus;∓&Mopf;𝕄&Mscr;ℳ&Mu;Μ",
    ['N'] =
    "&NJcy;Њ&Nacute;Ń&Ncaron;Ň&Ncedil;Ņ&Ncy;Н&NegativeMediumSpace;​&NegativeThickSpace;​&NegativeThinSpace;​"
    "&NegativeVeryThinSpace;​&NestedGreaterGreater;≫&NestedLessLess;≪&NewLine;\\n&Nfr;𝔑&NoBreak;⁠"
    "&NonBreakingSpace; &Nopf;ℕ&Not;⫬&NotCongruent;≢&NotCupCap;≭&NotDoubleVerticalBar;∦&NotElement;∉"
    "&NotEqual;≠&NotEqualTilde;≂̸&NotExists;∄&NotGreater;≯&NotGreaterEqual;≱&NotGreaterFullEqual;≧̸"
    "&NotGreaterGreater;≫̸&NotGreaterLess;≹&NotGreaterSlantEqual;⩾̸&NotGreaterTilde;≵&NotHumpDownHump;≎̸"
    "&NotHumpEqual;≏̸&NotLeftTriangle;⋪&NotLeftTriangleBar;⧏̸&NotLeftTriangleEqual;⋬&NotLess;≮"
    "&NotLessEqual;≰&NotLessGreater;≸&NotLessLess;≪̸&NotLessSlantEqual;⩽̸&NotLessTilde;≴&NotNestedGreaterGreater;⪢̸"
    "&NotNestedLessLess;⪡̸&NotPrecedes;⊀&NotPrecedesEqual;⪯̸&NotPrecedesSlantEqual;⋠&NotReverseElement;∌"
    "&NotRightTriangle;⋫&NotRightTriangleBar;⧐̸&NotRightTriangleEqual;⋭&NotSquareSubset;⊏̸"
    "&NotSquareSubsetEqual;⋢&NotSquareSuperset;⊐̸&NotSquareSupersetEqual;⋣&NotSubset;⊂⃒&NotSubsetEqual;⊈"
    "&NotSucceeds;⊁&NotSucceedsEqual;⪰̸&NotSucceedsSlantEqual;⋡&NotSucceedsTilde;≿̸&NotSuperset;⊃⃒"
    "&NotSupersetEqual;⊉&NotTilde;≁&NotTildeEqual;≄&NotTildeFullEqual;≇&NotTildeTilde;≉&NotVerticalBar;∤"
    "&Nscr;𝒩&Ntilde;Ñ&Nu;Ν",
    ['O'] =
    "&OElig;Œ&Oacute;Ó&Ocirc;Ô&Ocy;О&Odblac;Ő&Ofr;𝔒&Ograve;Ò&Omacr;Ō&Omega;Ω&Omicron;Ο&Oopf;𝕆"
    "&OpenCurlyDoubleQuote;“&OpenCurlyQuote;‘&Or;⩔&Oscr;𝒪&Oslash;Ø&Otilde;Õ&Otimes;⨷&Ouml;Ö"
    "&OverBar;‾&OverBrace;⏞&OverBracket;⎴&OverParenthesis;⏜",
    ['P'] =
    "&PartialD;∂&Pcy;П&Pfr;𝔓&Phi;Φ&Pi;Π&PlusMinus;±&Poincareplane;ℌ&Popf;ℙ&Pr;⪻&Precedes;≺"
    "&PrecedesEqual;⪯&PrecedesSlantEqual;≼&PrecedesTilde;≾&Prime;″&Product;∏&Proportion;∷&Proportional;∝"
    "&Pscr;𝒫&Psi;Ψ",
    ['Q'] =
    "&QUOT;\"&Qfr;𝔔&Qopf;ℚ&Qscr;𝒬",
    ['R'] =
    "&RBarr;⤐&REG;®&Racute;Ŕ&Rang;⟫&Rarr;↠&Rarrtl;⤖&Rcaron;Ř&Rcedil;Ŗ&Rcy;Р&Re;ℜ&ReverseElement;∋"
    "&ReverseEquilibrium;⇋&ReverseUpEquilibrium;⥯&Rfr;ℜ&Rho;Ρ&RightAngleBracket;⟩&RightArrow;→"
    "&RightArrowBar;⇥&RightArrowLeftArrow;⇄&RightCeiling;⌉&RightDoubleBracket;⟧&RightDownTeeVector;⥝"
    "&RightDownVector;⇂&RightDownVectorBar;⥕&RightFloor;⌋&RightTee;⊢&RightTeeArrow;↦&RightTeeVector;⥛"
    "&RightTriangle;⊳&RightTriangleBar;⧐&RightTriangleEqual;⊵&RightUpDownVector;⥏&RightUpTeeVector;⥜"
    "&RightUpVector;↾&RightUpVectorBar;⥔&RightVector;⇀&RightVectorBar;⥓&Rightarrow;⇒&Ropf;ℝ"
    "&RoundImplies;⥰&Rrightarrow;⇛&Rscr;ℛ&Rsh;↱&RuleDelayed;⧴",
    ['S'] =
    "&SHCHcy;Щ&SHcy;Ш&SOFTcy;Ь&Sacute;Ś&Sc;⪼&Scaron;Š&Scedil;Ş&Scirc;Ŝ&Scy;С&Sfr;𝔖&ShortDownArrow;↓"
    "&ShortLeftArrow;←&ShortRightArrow;→&ShortUpArrow;↑&Sigma;Σ&SmallCircle;∘&Sopf;𝕊&Sqrt;√"
    "&Square;□&SquareIntersection;⊓&SquareSubset;⊏&SquareSubsetEqual;⊑&SquareSuperset;⊐&SquareSupersetEqual;⊒"
    "&SquareUnion;⊔&Sscr;𝒮&Star;⋆&Sub;⋐&Subset;⋐&SubsetEqual;⊆&Succeeds;≻&SucceedsEqual;⪰"
    "&SucceedsSlantEqual;≽&SucceedsTilde;≿&SuchThat;∋&Sum;∑&Sup;⋑&Superset;⊃&SupersetEqual;⊇"
    "&Supset;⋑",
    ['T'] =
    "&THORN;Þ&TRADE;™&TSHcy;Ћ&TScy;Ц&Tab;   &Tau;Τ&Tcaron;Ť&Tcedil;Ţ&Tcy;Т&Tfr;𝔗&Therefore;∴&Theta;Θ"
    "&ThickSpace;  &ThinSpace; &Tilde;∼&TildeEqual;≃&TildeFullEqual;≅&TildeTilde;≈&Topf;𝕋"
    "&TripleDot;⃛&Tscr;𝒯&Tstrok;Ŧ",
    ['U'] =
    "&Uacute;Ú&Uarr;↟&Uarrocir;⥉&Ubrcy;Ў&Ubreve;Ŭ&Ucirc;Û&Ucy;У&Udblac;Ű&Ufr;𝔘&Ugrave;Ù&Umacr;Ū"
    "&UnderBar;_&UnderBrace;⏟&UnderBracket;⎵&UnderParenthesis;⏝&Union;⋃&UnionPlus;⊎&Uogon;Ų&Uopf;𝕌"
    "&UpArrow;↑&UpArrowBar;⤒&UpArrowDownArrow;⇅&UpDownArrow;↕&UpEquilibrium;⥮&UpTee;⊥&UpTeeArrow;↥"
    "&Uparrow;⇑&Updownarrow;⇕&UpperLeftArrow;↖&UpperRightArrow;↗&Upsi;ϒ&Upsilon;Υ&Uring;Ů&Uscr;𝒰"
    "&Utilde;Ũ&Uuml;Ü",
    ['V'] =
    "&VDash;⊫&Vbar;⫫&Vcy;В&Vdash;⊩&Vdashl;⫦&Vee;⋁&Verbar;‖&Vert;‖&VerticalBar;∣&VerticalLine;|"
    "&VerticalSeparator;❘&VerticalTilde;≀&VeryThinSpace; &Vfr;𝔙&Vopf;𝕍&Vscr;𝒱&Vvdash;⊪",
    ['W'] =
    "&Wcirc;Ŵ&Wedge;⋀&Wfr;𝔚&Wopf;𝕎&Wscr;𝒲",
    ['X'] =
    "&Xfr;𝔛&Xi;Ξ&Xopf;𝕏&Xscr;𝒳",
    ['Y'] =
    "&YAcy;Я&YIcy;Ї&YUcy;Ю&Yacute;Ý&Ycirc;Ŷ&Ycy;Ы&Yfr;𝔜&Yopf;𝕐&Yscr;𝒴&Yuml;Ÿ",
    ['Z'] =
    "&ZHcy;Ж&Zacute;Ź&Zcaron;Ž&Zcy;З&Zdot;Ż&ZeroWidthSpace;​&Zeta;Ζ&Zfr;ℨ&Zopf;ℤ&Zscr;𝒵",
    ['a'] =
    "&aacute;á&abreve;ă&ac;∾&acE;∾̳&acd;∿&acirc;â&acute;´&acy;а&aelig;æ&af;⁡&afr;𝔞&agrave;à"
    "&alefsym;ℵ&aleph;ℵ&alpha;α&amacr;ā&amalg;⨿&amp;&&and;∧&andand;⩕&andd;⩜&andslope;⩘&andv;⩚"
    "&ang;∠&ange;⦤&angle;∠&angmsd;∡&angmsdaa;⦨&angmsdab;⦩&angmsdac;⦪&angmsdad;⦫&angmsdae;⦬"
    "&angmsdaf;⦭&angmsdag;⦮&angmsdah;⦯&angrt;∟&angrtvb;⊾&angrtvbd;⦝&angsph;∢&angst;Å&angzarr;⍼"
    "&aogon;ą&aopf;𝕒&ap;≈&apE;⩰&apacir;⩯&ape;≊&apid;≋&apos;'&approx;≈&approxeq;≊&aring;å"
    "&ascr;𝒶&ast;*&asymp;≈&asympeq;≍&atilde;ã&auml;ä&awconint;∳&awint;⨑",
    ['b'] =
    "&bNot;⫭&backcong;≌&backepsilon;϶&backprime;‵&backsim;∽&backsimeq;⋍&barvee;⊽&barwed;⌅"
    "&barwedge;⌅&bbrk;⎵&bbrktbrk;⎶&bcong;≌&bcy;б&bdquo;„&becaus;∵&because;∵&bemptyv;⦰&bepsi;϶"
    "&bernou;ℬ&beta;β&beth;ℶ&between;≬&bfr;𝔟&bigcap;⋂&bigcirc;◯&bigcup;⋃&bigodot;⨀&bigoplus;⨁"
    "&bigotimes;⨂&bigsqcup;⨆&bigstar;★&bigtriangledown;▽&bigtriangleup;△&biguplus;⨄&bigvee;⋁"
    "&bigwedge;⋀&bkarow;⤍&blacklozenge;⧫&blacksquare;▪&blacktriangle;▴&blacktriangledown;▾"
    "&blacktriangleleft;◂&blacktriangleright;▸&blank;␣&blk12;▒&blk14;░&blk34;▓&block;█&bne;=⃥"
    "&bnequiv;≡⃥&bnot;⌐&bopf;𝕓&bot;⊥&bottom;⊥&bowtie;⋈&boxDL;╗&boxDR;╔&boxDl;╖&boxDr;╓"
    "&boxH;═&boxHD;╦&boxHU;╩&boxHd;╤&boxHu;╧&boxUL;╝&boxUR;╚&boxUl;╜&boxUr;╙&boxV;║&boxVH;╬"
    "&boxVL;╣&boxVR;╠&boxVh;╫&boxVl;╢&boxVr;╟&boxbox;⧉&boxdL;╕&boxdR;╒&boxdl;┐&boxdr;┌"
    "&boxh;─&boxhD;╥&boxhU;╨&boxhd;┬&boxhu;┴&boxminus;⊟&boxplus;⊞&boxtimes;⊠&boxuL;╛&boxuR;╘"
    "&boxul;┘&boxur;└&boxv;│&boxvH;╪&boxvL;╡&boxvR;╞&boxvh;┼&boxvl;┤&boxvr;├&bprime;‵&breve;˘"
    "&brvbar;¦&bscr;𝒷&bsemi;⁏&bsim;∽&bsime;⋍&bsol;\\&bsolb;⧅&bsolhsub;⟈&bull;•&bullet;•&bump;≎"
    "&bumpE;⪮&bumpe;≏&bumpeq;≏",
    ['c'] =
    "&cacute;ć&cap;∩&capand;⩄&capbrcup;⩉&capcap;⩋&capcup;⩇&capdot;⩀&caps;∩︀&caret;⁁&caron;ˇ"
    "&ccaps;⩍&ccaron;č&ccedil;ç&ccirc;ĉ&ccups;⩌&ccupssm;⩐&cdot;ċ&cedil;¸&cemptyv;⦲&cent;¢&centerdot;·"
    "&cfr;𝔠&chcy;ч&check;✓&checkmark;✓&chi;χ&cir;○&cirE;⧃&circ;ˆ&circeq;≗&circlearrowleft;↺"
    "&circlearrowright;↻&circledR;®&circledS;Ⓢ&circledast;⊛&circledcirc;⊚&circleddash;⊝&cire;≗"
    "&cirfnint;⨐&cirmid;⫯&cirscir;⧂&clubs;♣&clubsuit;♣&colon;:&colone;≔&coloneq;≔&comma;,&commat;@"
    "&comp;∁&compfn;∘&complement;∁&complexes;ℂ&cong;≅&congdot;⩭&conint;∮&copf;𝕔&coprod;∐"
    "&copy;©&copysr;℗&crarr;↵&cross;✗&cscr;𝒸&csub;⫏&csube;⫑&csup;⫐&csupe;⫒&ctdot;⋯&cudarrl;⤸"
    "&cudarrr;⤵&cuepr;⋞&cuesc;⋟&cularr;↶&cularrp;⤽&cup;∪&cupbrcap;⩈&cupcap;⩆&cupcup;⩊&cupdot;⊍"
    "&cupor;⩅&cups;∪︀&curarr;↷&curarrm;⤼&curlyeqprec;⋞&curlyeqsucc;⋟&curlyvee;⋎&curlywedge;⋏"
    "&curren;¤&curvearrowleft;↶&curvearrowright;↷&cuvee;⋎&cuwed;⋏&cwconint;∲&cwint;∱&cylcty;⌭",
    ['d'] =
    "&dArr;⇓&dHar;⥥&dagger;†&daleth;ℸ&darr;↓&dash;‐&dashv;⊣&dbkarow;⤏&dblac;˝&dcaron;ď&dcy;д"
    "&dd;ⅆ&ddagger;‡&ddarr;⇊&ddotseq;⩷&deg;°&delta;δ&demptyv;⦱&dfisht;⥿&dfr;𝔡&dharl;⇃&dharr;⇂"
    "&diam;⋄&diamond;⋄&diamondsuit;♦&diams;♦&die;¨&digamma;ϝ&disin;⋲&div;÷&divide;÷&divideontimes;⋇"
    "&divonx;⋇&djcy;ђ&dlcorn;⌞&dlcrop;⌍&dollar;$&dopf;𝕕&dot;˙&doteq;≐&doteqdot;≑&dotminus;∸"
    "&dotplus;∔&dotsquare;⊡&doublebarwedge;⌆&downarrow;↓&downdownarrows;⇊&downharpoonleft;⇃"
    "&downharpoonright;⇂&drbkarow;⤐&drcorn;⌟&drcrop;⌌&dscr;𝒹&dscy;ѕ&dsol;⧶&dstrok;đ&dtdot;⋱"
    "&dtri;▿&dtrif;▾&duarr;⇵&duhar;⥯&dwangle;⦦&dzcy;џ&dzigrarr;⟿",
    ['e'] =
    "&eDDot;⩷&eDot;≑&eacute;é&easter;⩮&ecaron;ě&ecir;≖&ecirc;ê&ecolon;≕&ecy;э&edot;ė&ee;ⅇ&efDot;≒"
    "&efr;𝔢&eg;⪚&egrave;è&egs;⪖&egsdot;⪘&el;⪙&elinters;⏧&ell;ℓ&els;⪕&elsdot;⪗&emacr;ē&empty;∅"
    "&emptyset;∅&emptyv;∅&emsp13; &emsp14; &emsp; &eng;ŋ&ensp; &eogon;ę&eopf;𝕖&epar;⋕&eparsl;⧣"
    "&eplus;⩱&epsi;ε&epsilon;ε&epsiv;ϵ&eqcirc;≖&eqcolon;≕&eqsim;≂&eqslantgtr;⪖&eqslantless;⪕"
    "&equals;=&equest;≟&equiv;≡&equivDD;⩸&eqvparsl;⧥&erDot;≓&erarr;⥱&escr;ℯ&esdot;≐&esim;≂"
    "&eta;η&eth;ð&euml;ë&euro;€&excl;!&exist;∃&expectation;ℰ&exponentiale;ⅇ",
    ['f'] =
    "&fallingdotseq;≒&fcy;ф&female;♀&ffilig;ﬃ&fflig;ﬀ&ffllig;ﬄ&ffr;𝔣&filig;ﬁ&fjlig;fj&flat;♭"
    "&fllig;ﬂ&fltns;▱&fnof;ƒ&fopf;𝕗&forall;∀&fork;⋔&forkv;⫙&fpartint;⨍&frac12;½&frac13;⅓"
    "&frac14;¼&frac15;⅕&frac16;⅙&frac18;⅛&frac23;⅔&frac25;⅖&frac34;¾&frac35;⅗&frac38;⅜&frac45;⅘"
    "&frac56;⅚&frac58;⅝&frac78;⅞&frasl;⁄&frown;⌢&fscr;𝒻",
    ['g'] =
    "&gE;≧&gEl;⪌&gacute;ǵ&gamma;γ&gammad;ϝ&gap;⪆&gbreve;ğ&gcirc;ĝ&gcy;г&gdot;ġ&ge;≥&gel;⋛&geq;≥"
    "&geqq;≧&geqslant;⩾&ges;⩾&gescc;⪩&gesdot;⪀&gesdoto;⪂&gesdotol;⪄&gesl;⋛︀&gesles;⪔&gfr;𝔤"
    "&gg;≫&ggg;⋙&gimel;ℷ&gjcy;ѓ&gl;≷&glE;⪒&gla;⪥&glj;⪤&gnE;≩&gnap;⪊&gnapprox;⪊&gne;⪈&gneq;⪈"
    "&gneqq;≩&gnsim;⋧&gopf;𝕘&grave;`&gscr;ℊ&gsim;≳&gsime;⪎&gsiml;⪐&gt;>&gtcc;⪧&gtcir;⩺&gtdot;⋗"
    "&gtlPar;⦕&gtquest;⩼&gtrapprox;⪆&gtrarr;⥸&gtrdot;⋗&gtreqless;⋛&gtreqqless;⪌&gtrless;≷"
    "&gtrsim;≳&gvertneqq;≩︀&gvnE;≩︀",
    ['h'] =
    "&hArr;⇔&hairsp; &half;½&hamilt;ℋ&hardcy;ъ&harr;↔&harrcir;⥈&harrw;↭&hbar;ℏ&hcirc;ĥ&hearts;♥"
    "&heartsuit;♥&hellip;…&hercon;⊹&hfr;𝔥&hksearow;⤥&hkswarow;⤦&hoarr;⇿&homtht;∻&hookleftarrow;↩"
    "&hookrightarrow;↪&hopf;𝕙&horbar;―&hscr;𝒽&hslash;ℏ&hstrok;ħ&hybull;⁃&hyphen;‐",
    ['i'] =
    "&iacute;í&ic;⁣&icirc;î&icy;и&iecy;е&iexcl;¡&iff;⇔&ifr;𝔦&igrave;ì&ii;ⅈ&iiiint;⨌&iiint;∭"
    "&iinfin;⧜&iiota;℩&ijlig;ĳ&imacr;ī&image;ℑ&imagline;ℐ&imagpart;ℑ&imath;ı&imof;⊷&imped;Ƶ"
    "&in;∈&incare;℅&infin;∞&infintie;⧝&inodot;ı&int;∫&intcal;⊺&integers;ℤ&intercal;⊺&intlarhk;⨗"
    "&intprod;⨼&iocy;ё&iogon;į&iopf;𝕚&iota;ι&iprod;⨼&iquest;¿&iscr;𝒾&isin;∈&isinE;⋹&isindot;⋵"
    "&isins;⋴&isinsv;⋳&isinv;∈&it;⁢&itilde;ĩ&iukcy;і&iuml;ï",
    ['j'] =
    "&jcirc;ĵ&jcy;й&jfr;𝔧&jmath;ȷ&jopf;𝕛&jscr;𝒿&jsercy;ј&jukcy;є",
    ['k'] =
    "&kappa;κ&kappav;ϰ&kcedil;ķ&kcy;к&kfr;𝔨&kgreen;ĸ&khcy;х&kjcy;ќ&kopf;𝕜&kscr;𝓀",
    ['l'] =
    "&lAarr;⇚&lArr;⇐&lAtail;⤛&lBarr;⤎&lE;≦&lEg;⪋&lHar;⥢&lacute;ĺ&laemptyv;⦴&lagran;ℒ&lambda;λ"
    "&lang;⟨&langd;⦑&langle;⟨&lap;⪅&laquo;«&larr;←&larrb;⇤&larrbfs;⤟&larrfs;⤝&larrhk;↩&larrlp;↫"
    "&larrpl;⤹&larrsim;⥳&larrtl;↢&lat;⪫&latail;⤙&late;⪭&lates;⪭︀&lbarr;⤌&lbbrk;❲&lbrace;{"
    "&lbrack;[&lbrke;⦋&lbrksld;⦏&lbrkslu;⦍&lcaron;ľ&lcedil;ļ&lceil;⌈&lcub;{&lcy;л&ldca;⤶&ldquo;“"
    "&ldquor;„&ldrdhar;⥧&ldrushar;⥋&ldsh;↲&le;≤&leftarrow;←&leftarrowtail;↢&leftharpoondown;↽"
    "&leftharpoonup;↼&leftleftarrows;⇇&leftrightarrow;↔&leftrightarrows;⇆&leftrightharpoons;⇋"
    "&leftrightsquigarrow;↭&leftthreetimes;⋋&leg;⋚&leq;≤&leqq;≦&leqslant;⩽&les;⩽&lescc;⪨"
    "&lesdot;⩿&lesdoto;⪁&lesdotor;⪃&lesg;⋚︀&lesges;⪓&lessapprox;⪅&lessdot;⋖&lesseqgtr;⋚"
    "&lesseqqgtr;⪋&lessgtr;≶&lesssim;≲&lfisht;⥼&lfloor;⌊&lfr;𝔩&lg;≶&lgE;⪑&lhard;↽&lharu;↼"
    "&lharul;⥪&lhblk;▄&ljcy;љ&ll;≪&llarr;⇇&llcorner;⌞&llhard;⥫&lltri;◺&lmidot;ŀ&lmoust;⎰"
    "&lmoustache;⎰&lnE;≨&lnap;⪉&lnapprox;⪉&lne;⪇&lneq;⪇&lneqq;≨&lnsim;⋦&loang;⟬&loarr;⇽"
    "&lobrk;⟦&longleftarrow;⟵&longleftrightarrow;⟷&longmapsto;⟼&longrightarrow;⟶&looparrowleft;↫"
    "&looparrowright;↬&lopar;⦅&lopf;𝕝&loplus;⨭&lotimes;⨴&lowast;∗&lowbar;_&loz;◊&lozenge;◊"
    "&lozf;⧫&lpar;(&lparlt;⦓&lrarr;⇆&lrcorner;⌟&lrhar;⇋&lrhard;⥭&lrm;‎&lrtri;⊿&lsaquo;‹&lscr;𝓁"
    "&lsh;↰&lsim;≲&lsime;⪍&lsimg;⪏&lsqb;[&lsquo;‘&lsquor;‚&lstrok;ł&lt;<&ltcc;⪦&ltcir;⩹&ltdot;⋖"
    "&lthree;⋋&ltimes;⋉&ltlarr;⥶&ltquest;⩻&ltrPar;⦖&ltri;◃&ltrie;⊴&ltrif;◂&lurdshar;⥊&luruhar;⥦"
    "&lvertneqq;≨︀&lvnE;≨︀",
    ['m'] =
    "&mDDot;∺&macr;¯&male;♂&malt;✠&maltese;✠&map;↦&mapsto;↦&mapstodown;↧&mapstoleft;↤&mapstoup;↥"
    "&marker;▮&mcomma;⨩&mcy;м&mdash;—&measuredangle;∡&mfr;𝔪&mho;℧&micro;µ&mid;∣&midast;*&midcir;⫰"
    "&middot;·&minus;−&minusb;⊟&minusd;∸&minusdu;⨪&mlcp;⫛&mldr;…&mnplus;∓&models;⊧&mopf;𝕞"
    "&mp;∓&mscr;𝓂&mstpos;∾&mu;μ&multimap;⊸&mumap;⊸",
    ['n'] =
    "&nGg;⋙̸&nGt;≫⃒&nGtv;≫̸&nLeftarrow;⇍&nLeftrightarrow;⇎&nLl;⋘̸&nLt;≪⃒&nLtv;≪̸"
    "&nRightarrow;⇏&nVDash;⊯&nVdash;⊮&nabla;∇&nacute;ń&nang;∠⃒&nap;≉&napE;⩰̸&napid;≋̸"
    "&napos;ŉ&napprox;≉&natur;♮&natural;♮&naturals;ℕ&nbsp; &nbump;≎̸&nbumpe;≏̸&ncap;⩃&ncaron;ň"
    "&ncedil;ņ&ncong;≇&ncongdot;⩭̸&ncup;⩂&ncy;н&ndash;–&ne;≠&neArr;⇗&nearhk;⤤&nearr;↗&nearrow;↗"
    "&nedot;≐̸&nequiv;≢&nesear;⤨&nesim;≂̸&nexist;∄&nexists;∄&nfr;𝔫&ngE;≧̸&nge;≱&ngeq;≱"
    "&ngeqq;≧̸&ngeqslant;⩾̸&nges;⩾̸&ngsim;≵&ngt;≯&ngtr;≯&nhArr;⇎&nharr;↮&nhpar;⫲&ni;∋"
    "&nis;⋼&nisd;⋺&niv;∋&njcy;њ&nlArr;⇍&nlE;≦̸&nlarr;↚&nldr;‥&nle;≰&nleftarrow;↚&nleftrightarrow;↮"
    "&nleq;≰&nleqq;≦̸&nleqslant;⩽̸&nles;⩽̸&nless;≮&nlsim;≴&nlt;≮&nltri;⋪&nltrie;⋬&nmid;∤"
    "&nopf;𝕟&not;¬&notin;∉&notinE;⋹̸&notindot;⋵̸&notinva;∉&notinvb;⋷&notinvc;⋶&notni;∌"
    "&notniva;∌&notnivb;⋾&notnivc;⋽&npar;∦&nparallel;∦&nparsl;⫽⃥&npart;∂̸&npolint;⨔&npr;⊀"
    "&nprcue;⋠&npre;⪯̸&nprec;⊀&npreceq;⪯̸&nrArr;⇏&nrarr;↛&nrarrc;⤳̸&nrarrw;↝̸&nrightarrow;↛"
    "&nrtri;⋫&nrtrie;⋭&nsc;⊁&nsccue;⋡&nsce;⪰̸&nscr;𝓃&nshortmid;∤&nshortparallel;∦&nsim;≁"
    "&nsime;≄&nsimeq;≄&nsmid;∤&nspar;∦&nsqsube;⋢&nsqsupe;⋣&nsub;⊄&nsubE;⫅̸&nsube;⊈&nsubset;⊂⃒"
    "&nsubseteq;⊈&nsubseteqq;⫅̸&nsucc;⊁&nsucceq;⪰̸&nsup;⊅&nsupE;⫆̸&nsupe;⊉&nsupset;⊃⃒"
    "&nsupseteq;⊉&nsupseteqq;⫆̸&ntgl;≹&ntilde;ñ&ntlg;≸&ntriangleleft;⋪&ntrianglelefteq;⋬&ntriangleright;⋫"
    "&ntrianglerighteq;⋭&nu;ν&num;#&numero;№&numsp; &nvDash;⊭&nvHarr;⤄&nvap;≍⃒&nvdash;⊬&nvge;≥⃒"
    "&nvgt;>⃒&nvinfin;⧞&nvlArr;⤂&nvle;≤⃒&nvlt;<⃒&nvltrie;⊴⃒&nvrArr;⤃&nvrtrie;⊵⃒&nvsim;∼⃒"
    "&nwArr;⇖&nwarhk;⤣&nwarr;↖&nwarrow;↖&nwnear;⤧",
    ['o'] =
    "&oS;Ⓢ&oacute;ó&oast;⊛&ocir;⊚&ocirc;ô&ocy;о&odash;⊝&odblac;ő&odiv;⨸&odot;⊙&odsold;⦼&oelig;œ"
    "&ofcir;⦿&ofr;𝔬&ogon;˛&ograve;ò&ogt;⧁&ohbar;⦵&ohm;Ω&oint;∮&olarr;↺&olcir;⦾&olcross;⦻"
    "&oline;‾&olt;⧀&omacr;ō&omega;ω&omicron;ο&omid;⦶&ominus;⊖&oopf;𝕠&opar;⦷&operp;⦹&oplus;⊕"
    "&or;∨&orarr;↻&ord;⩝&order;ℴ&orderof;ℴ&ordf;ª&ordm;º&origof;⊶&oror;⩖&orslope;⩗&orv;⩛"
    "&oscr;ℴ&oslash;ø&osol;⊘&otilde;õ&otimes;⊗&otimesas;⨶&ouml;ö&ovbar;⌽",
    ['p'] =
    "&par;∥&para;¶&parallel;∥&parsim;⫳&parsl;⫽&part;∂&pcy;п&percnt;%&period;.&permil;‰&perp;⊥"
    "&pertenk;‱&pfr;𝔭&phi;φ&phiv;ϕ&phmmat;ℳ&phone;☎&pi;π&pitchfork;⋔&piv;ϖ&planck;ℏ&planckh;ℎ"
    "&plankv;ℏ&plus;+&plusacir;⨣&plusb;⊞&pluscir;⨢&plusdo;∔&plusdu;⨥&pluse;⩲&plusmn;±&plussim;⨦"
    "&plustwo;⨧&pm;±&pointint;⨕&popf;𝕡&pound;£&pr;≺&prE;⪳&prap;⪷&prcue;≼&pre;⪯&prec;≺&precapprox;⪷"
    "&preccurlyeq;≼&preceq;⪯&precnapprox;⪹&precneqq;⪵&precnsim;⋨&precsim;≾&prime;′&primes;ℙ"
    "&prnE;⪵&prnap;⪹&prnsim;⋨&prod;∏&profalar;⌮&profline;⌒&profsurf;⌓&prop;∝&propto;∝&prsim;≾"
    "&prurel;⊰&pscr;𝓅&psi;ψ&puncsp; ",
    ['q'] =
    "&qfr;𝔮&qint;⨌&qopf;𝕢&qprime;⁗&qscr;𝓆&quaternions;ℍ&quatint;⨖&quest;?&questeq;≟&quot;\"",
    ['r'] =
    "&rAarr;⇛&rArr;⇒&rAtail;⤜&rBarr;⤏&rHar;⥤&race;∽̱&racute;ŕ&radic;√&raemptyv;⦳&rang;⟩"
    "&rangd;⦒&range;⦥&rangle;⟩&raquo;»&rarr;→&rarrap;⥵&rarrb;⇥&rarrbfs;⤠&rarrc;⤳&rarrfs;⤞"
    "&rarrhk;↪&rarrlp;↬&rarrpl;⥅&rarrsim;⥴&rarrtl;↣&rarrw;↝&ratail;⤚&ratio;∶&rationals;ℚ"
    "&rbarr;⤍&rbbrk;❳&rbrace;}&rbrack;]&rbrke;⦌&rbrksld;⦎&rbrkslu;⦐&rcaron;ř&rcedil;ŗ&rceil;⌉"
    "&rcub;}&rcy;р&rdca;⤷&rdldhar;⥩&rdquo;”&rdquor;”&rdsh;↳&real;ℜ&realine;ℛ&realpart;ℜ&reals;ℝ"
    "&rect;▭&reg;®&rfisht;⥽&rfloor;⌋&rfr;𝔯&rhard;⇁&rharu;⇀&rharul;⥬&rho;ρ&rhov;ϱ&rightarrow;→"
    "&rightarrowtail;↣&rightharpoondown;⇁&rightharpoonup;⇀&rightleftarrows;⇄&rightleftharpoons;⇌"
    "&rightrightarrows;⇉&rightsquigarrow;↝&rightthreetimes;⋌&ring;˚&risingdotseq;≓&rlarr;⇄&rlhar;⇌"
    "&rlm;‏&rmoust;⎱&rmoustache;⎱&rnmid;⫮&roang;⟭&roarr;⇾&robrk;⟧&ropar;⦆&ropf;𝕣&roplus;⨮"
    "&rotimes;⨵&rpar;)&rpargt;⦔&rppolint;⨒&rrarr;⇉&rsaquo;›&rscr;𝓇&rsh;↱&rsqb;]&rsquo;’&rsquor;’"
    "&rthree;⋌&rtimes;⋊&rtri;▹&rtrie;⊵&rtrif;▸&rtriltri;⧎&ruluhar;⥨&rx;℞",
    ['s'] =
    "&sacute;ś&sbquo;‚&sc;≻&scE;⪴&scap;⪸&scaron;š&sccue;≽&sce;⪰&scedil;ş&scirc;ŝ&scnE;⪶&scnap;⪺"
    "&scnsim;⋩&scpolint;⨓&scsim;≿&scy;с&sdot;⋅&sdotb;⊡&sdote;⩦&seArr;⇘&searhk;⤥&searr;↘"
    "&searrow;↘&sect;§&semi;;&seswar;⤩&setminus;∖&setmn;∖&sext;✶&sfr;𝔰&sfrown;⌢&sharp;♯&shchcy;щ"
    "&shcy;ш&shortmid;∣&shortparallel;∥&shy;­&sigma;σ&sigmaf;ς&sigmav;ς&sim;∼&simdot;⩪&sime;≃"
    "&simeq;≃&simg;⪞&simgE;⪠&siml;⪝&simlE;⪟&simne;≆&simplus;⨤&simrarr;⥲&slarr;←&smallsetminus;∖"
    "&smashp;⨳&smeparsl;⧤&smid;∣&smile;⌣&smt;⪪&smte;⪬&smtes;⪬︀&softcy;ь&sol;/&solb;⧄&solbar;⌿"
    "&sopf;𝕤&spades;♠&spadesuit;♠&spar;∥&sqcap;⊓&sqcaps;⊓︀&sqcup;⊔&sqcups;⊔︀&sqsub;⊏"
    "&sqsube;⊑&sqsubset;⊏&sqsubseteq;⊑&sqsup;⊐&sqsupe;⊒&sqsupset;⊐&sqsupseteq;⊒&squ;□&square;□"
    "&squarf;▪&squf;▪&srarr;→&sscr;𝓈&ssetmn;∖&ssmile;⌣&sstarf;⋆&star;☆&starf;★&straightepsilon;ϵ"
    "&straightphi;ϕ&strns;¯&sub;⊂&subE;⫅&subdot;⪽&sube;⊆&subedot;⫃&submult;⫁&subnE;⫋&subne;⊊"
    "&subplus;⪿&subrarr;⥹&subset;⊂&subseteq;⊆&subseteqq;⫅&subsetneq;⊊&subsetneqq;⫋&subsim;⫇"
    "&subsub;⫕&subsup;⫓&succ;≻&succapprox;⪸&succcurlyeq;≽&succeq;⪰&succnapprox;⪺&succneqq;⪶"
    "&succnsim;⋩&succsim;≿&sum;∑&sung;♪&sup1;¹&sup2;²&sup3;³&sup;⊃&supE;⫆&supdot;⪾&supdsub;⫘"
    "&supe;⊇&supedot;⫄&suphsol;⟉&suphsub;⫗&suplarr;⥻&supmult;⫂&supnE;⫌&supne;⊋&supplus;⫀"
    "&supset;⊃&supseteq;⊇&supseteqq;⫆&supsetneq;⊋&supsetneqq;⫌&supsim;⫈&supsub;⫔&supsup;⫖"
    "&swArr;⇙&swarhk;⤦&swarr;↙&swarrow;↙&swnwar;⤪&szlig;ß",
    ['t'] =
    "&target;⌖&tau;τ&tbrk;⎴&tcaron;ť&tcedil;ţ&tcy;т&tdot;⃛&telrec;⌕&tfr;𝔱&there4;∴&therefore;∴"
    "&theta;θ&thetasym;ϑ&thetav;ϑ&thickapprox;≈&thicksim;∼&thinsp; &thkap;≈&thksim;∼&thorn;þ"
    "&tilde;˜&times;×&timesb;⊠&timesbar;⨱&timesd;⨰&tint;∭&toea;⤨&top;⊤&topbot;⌶&topcir;⫱"
    "&topf;𝕥&topfork;⫚&tosa;⤩&tprime;‴&trade;™&triangle;▵&triangledown;▿&triangleleft;◃"
    "&trianglelefteq;⊴&triangleq;≜&triangleright;▹&trianglerighteq;⊵&tridot;◬&trie;≜&triminus;⨺"
    "&triplus;⨹&trisb;⧍&tritime;⨻&trpezium;⏢&tscr;𝓉&tscy;ц&tshcy;ћ&tstrok;ŧ&twixt;≬&twoheadleftarrow;↞"
    "&twoheadrightarrow;↠",
    ['u'] =
    "&uArr;⇑&uHar;⥣&uacute;ú&uarr;↑&ubrcy;ў&ubreve;ŭ&ucirc;û&ucy;у&udarr;⇅&udblac;ű&udhar;⥮"
    "&ufisht;⥾&ufr;𝔲&ugrave;ù&uharl;↿&uharr;↾&uhblk;▀&ulcorn;⌜&ulcorner;⌜&ulcrop;⌏&ultri;◸"
    "&umacr;ū&uml;¨&uogon;ų&uopf;𝕦&uparrow;↑&updownarrow;↕&upharpoonleft;↿&upharpoonright;↾"
    "&uplus;⊎&upsi;υ&upsih;ϒ&upsilon;υ&upuparrows;⇈&urcorn;⌝&urcorner;⌝&urcrop;⌎&uring;ů&urtri;◹"
    "&uscr;𝓊&utdot;⋰&utilde;ũ&utri;▵&utrif;▴&uuarr;⇈&uuml;ü&uwangle;⦧",
    ['v'] =
    "&vArr;⇕&vBar;⫨&vBarv;⫩&vDash;⊨&vangrt;⦜&varepsilon;ϵ&varkappa;ϰ&varnothing;∅&varphi;ϕ"
    "&varpi;ϖ&varpropto;∝&varr;↕&varrho;ϱ&varsigma;ς&varsubsetneq;⊊︀&varsubsetneqq;⫋︀&varsupsetneq;⊋︀"
    "&varsupsetneqq;⫌︀&vartheta;ϑ&vartriangleleft;⊲&vartriangleright;⊳&vcy;в&vdash;⊢&vee;∨"
    "&veebar;⊻&veeeq;≚&vellip;⋮&verbar;|&vert;|&vfr;𝔳&vltri;⊲&vnsub;⊂⃒&vnsup;⊃⃒&vopf;𝕧"
    "&vprop;∝&vrtri;⊳&vscr;𝓋&vsubnE;⫋︀&vsubne;⊊︀&vsupnE;⫌︀&vsupne;⊋︀&vzigzag;⦚",
    ['w'] =
    "&wcirc;ŵ&wedbar;⩟&wedge;∧&wedgeq;≙&weierp;℘&wfr;𝔴&wopf;𝕨&wp;℘&wr;≀&wreath;≀&wscr;𝓌",
    ['x'] =
    "&xcap;⋂&xcirc;◯&xcup;⋃&xdtri;▽&xfr;𝔵&xhArr;⟺&xharr;⟷&xi;ξ&xlArr;⟸&xlarr;⟵&xmap;⟼"
    "&xnis;⋻&xodot;⨀&xopf;𝕩&xoplus;⨁&xotime;⨂&xrArr;⟹&xrarr;⟶&xscr;𝓍&xsqcup;⨆&xuplus;⨄"
    "&xutri;△&xvee;⋁&xwedge;⋀",
    ['y'] =
    "&yacute;ý&yacy;я&ycirc;ŷ&ycy;ы&yen;¥&yfr;𝔶&yicy;ї&yopf;𝕪&yscr;𝓎&yucy;ю&yuml;ÿ",
    ['z'] =
    "&zacute;ź&zcaron;ž&zcy;з&zdot;ż&zeetrf;ℨ&zeta;ζ&zfr;𝔷&zhcy;ж&zigrarr;⇝&zopf;𝕫&zscr;𝓏"
    "&zwj;‍&zwnj;‌",
};

// A char mask improves the performance of character comparison by reducing the number of checked conditions.
// We must use `unsigned char *` for input because the mask is only defined for non-negative indexes.

static const char CHARMASK_WHITESPACE[1 + (unsigned char) -1] = {
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
};

static const char CHARMASK_ATTRIBUTE_NAME_END[1 + (unsigned char) -1] = {
    [ '='] = 1,
    ['\0'] = 1,
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
    [ '>'] = 1,
};

static const char CHARMASK_ATTRIBUTE_VALUE_END[1 + (unsigned char) -1] = {
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
    [ '>'] = 1,
    ['\0'] = 1,
};

static const char CHARMASK_VALID_TAG_NAME_START[1 + (unsigned char) -1] = {
    // https://dev.w3.org/html5/spec-LC/syntax.html#syntax-tag-name
    // The `–` for custom elements is yet to be incorporated into this standard.

    ['a'] = 1, ['b'] = 1, ['c'] = 1, ['d'] = 1, ['e'] = 1, ['f'] = 1, ['g'] = 1, ['h'] = 1,
    ['i'] = 1, ['j'] = 1, ['k'] = 1, ['l'] = 1, ['m'] = 1, ['n'] = 1, ['o'] = 1, ['p'] = 1,
    ['q'] = 1, ['r'] = 1, ['s'] = 1, ['t'] = 1, ['u'] = 1, ['v'] = 1, ['w'] = 1, ['x'] = 1,
    ['y'] = 1, ['z'] = 1,

    ['A'] = 1, ['B'] = 1, ['C'] = 1, ['D'] = 1, ['E'] = 1, ['F'] = 1, ['G'] = 1, ['H'] = 1,
    ['I'] = 1, ['J'] = 1, ['K'] = 1, ['L'] = 1, ['M'] = 1, ['N'] = 1, ['O'] = 1, ['P'] = 1,
    ['Q'] = 1, ['R'] = 1, ['S'] = 1, ['T'] = 1, ['U'] = 1, ['V'] = 1, ['W'] = 1, ['X'] = 1,
    ['Y'] = 1, ['Z'] = 1,
};

static const char CHARMASK_VALID_TAG_NAME[1 + (unsigned char) -1] = {
    ['a'] = 1, ['b'] = 1, ['c'] = 1, ['d'] = 1, ['e'] = 1, ['f'] = 1, ['g'] = 1, ['h'] = 1,
    ['i'] = 1, ['j'] = 1, ['k'] = 1, ['l'] = 1, ['m'] = 1, ['n'] = 1, ['o'] = 1, ['p'] = 1,
    ['q'] = 1, ['r'] = 1, ['s'] = 1, ['t'] = 1, ['u'] = 1, ['v'] = 1, ['w'] = 1, ['x'] = 1,
    ['y'] = 1, ['z'] = 1,

    ['A'] = 1, ['B'] = 1, ['C'] = 1, ['D'] = 1, ['E'] = 1, ['F'] = 1, ['G'] = 1, ['H'] = 1,
    ['I'] = 1, ['J'] = 1, ['K'] = 1, ['L'] = 1, ['M'] = 1, ['N'] = 1, ['O'] = 1, ['P'] = 1,
    ['Q'] = 1, ['R'] = 1, ['S'] = 1, ['T'] = 1, ['U'] = 1, ['V'] = 1, ['W'] = 1, ['X'] = 1,
    ['Y'] = 1, ['Z'] = 1,

    ['0'] = 1, ['1'] = 1, ['2'] = 1, ['3'] = 1, ['4'] = 1, ['5'] = 1, ['6'] = 1, ['7'] = 1,
    ['8'] = 1, ['9'] = 1,

    ['-'] = 1,
};

struct String {
    char *data;
    size_t length;
    bool is_malloced;
};

#define STRING(cstring) (struct String) {cstring, sizeof cstring - 1, 0}
#define NULL_STRING (struct String) {NULL, 0, false}

void String_free(struct String string)
{
    if (string.is_malloced && string.data != NULL) {
        free(string.data);
    }
}

static size_t entities_to_utf8(const char *input, size_t input_length, char *output,
    bool skip_stray_tags)
{
    // When using this function we make use of the fact that the number of bytes written to output
    // is never greater than `input_length`.

    size_t i = 0, k;
    const char *original_output = output;
    for (i = 0; i < input_length; ++i) {
        if (skip_stray_tags && input[i] == '<' && i + 1 < input_length &&
            (input[i + 1] == '/' || CHARMASK_VALID_TAG_NAME_START[(unsigned char) input[i + 1]]))
        {
            do {
                i += 1;
            } while (i < input_length && input[i] != '>');
            continue;
        }
        if (input[i] != '&') {
            *output++ = input[i];
            continue;
        }
        if (input[i + 1] == '#') {
            uint_fast32_t codepoint = 0;
            if (input[i + 2] == 'x') {
                for (k = 3; input[i + k] != ';'; ++k) {
                    if (input[i + k] >= '0' && input[i + k] <= '9') {
                        codepoint = codepoint * 16 + (input[i + k] - '0');
                    }
                    else if (input[i + k] >= 'A' && input[i + k] <= 'F') {
                        codepoint = codepoint * 16 + (10 + input[i + k] - 'A');
                    }
                    else if (input[i + k] >= 'a' && input[i + k] <= 'f') {
                        codepoint = codepoint * 16 + (10 + input[i + k] - 'a');
                    }
                    else {
                        codepoint = -1;
                        break;
                    }
                }
            }
            else {
                for (k = 2; input[i + k] != ';'; ++k) {
                    if (input[i + k] >= '0' && input[i + k] <= '9') {
                        codepoint = codepoint * 10 + (input[i + k] - '0');
                    }
                    else {
                        codepoint = -1;
                        break;
                    }
                }
            }
            if (codepoint > 0x7FFFFFFF) {
                *output++ = '&';
                continue;
            }
            i += k;

            // See `man utf-8`

            if (codepoint <= 0x7F) {
                *output++ = codepoint;
            }
            else if (codepoint <= 0x7FF) {
                *output++ = 0b11000000 + (codepoint >> 6);
                *output++ = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0xFFFF) {
                *output++ = 0b11100000 + (codepoint >> 12);
                *output++ = (10 << 6) + ((codepoint >> 6) & 0b111111);
                *output++ = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x1FFFFF) {
                *output++ = 0b11110000 + (codepoint >> 18);
                *output++ = (10 << 6) + ((codepoint >> 12) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 6) & 0b111111);
                *output++ = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x03FFFFFF) {
                *output++ = 0b11111000 + (codepoint >> 24);
                *output++ = (10 << 6) + ((codepoint >> 18) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 12) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 6) & 0b111111);
                *output++ = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x7FFFFFFF) {
                *output++ = 0b1111110 + (codepoint >> 30);
                *output++ = (10 << 6) + ((codepoint >> 24) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 18) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 12) & 0b111111);
                *output++ = (10 << 6) + ((codepoint >> 6) & 0b111111);
                *output++ = (10 << 6) + (codepoint & 0b111111);
            }
            continue;
        }
        if (i + 1 == input_length || ENTITIES[(unsigned char) input[i + 1]] == NULL) {
            *output++ = '&';
            continue;
        }
        char entity[40] = {'&'};
        k = 1;
        do {
            if (k == sizeof entity - 1 || i + k == input_length) {
                break;
            }
            entity[k] = input[i + k];
        } while (entity[k++] != ';');
        if (entity[k - 1] != ';') {
            *output++ = '&';
            continue;
        }
        entity[k] = '\0';
        const char *pos = strstr(ENTITIES[(unsigned char) entity[1]], entity);
        if (pos == NULL) {
            *output++ = '&';
            continue;
        }
        i += k - 1;
        if (pos[k] == '&') { // Special case for the &amp; entity
            *output++ = '&';
        }
        while (pos[k] != '&' && pos[k] != '\0') {
            *output++ = pos[k++];
        }
    }
    return output - original_output;
}

static struct String entities_to_utf8_malloc(const char *input, size_t length, bool skip_stray_tags)
{
    if (length == 0) {
        return (struct String) {"", 0, false};
    }
    char *buffer = malloc(length);
    if (buffer == NULL) {
        return NULL_STRING;
    }
    size_t buffer_length = entities_to_utf8(input, length, buffer, skip_stray_tags);
    char *buffer_realloc = realloc(buffer, buffer_length);
    if (buffer_realloc == NULL) {
        free(buffer);
        return NULL_STRING;
    }
    return (struct String) {buffer_realloc, buffer_length, true};

}

static int_fast16_t strnicmp(const char *s1, const char *s2, size_t length)
{
    int_fast16_t diff = 0;
    while (length--) {
        if (diff = *s1 - *s2) {
            if ((unsigned char) (*s1 - 'A') <= 'Z' - 'A') {
                diff += 'a' - 'A';
            }
            if ((unsigned char) (*s2 - 'A') <= 'Z' - 'A') {
                diff -= 'a' - 'A';
            }
            if (diff != 0) {
                break;
            }
        }
        if (*s1 == '\0') {
            break;
        }
        s1++;
        s2++;
    }
    return diff;
}

/*****************************************************************************/
/* Data types */

struct HtmlDocument {
    // According to benchmarks, cache locality is very important in the nodes array but not in the
    // attributes array. The node struct size must be as small as possible.

    const char *html;
    size_t node_count;
    struct Node {
        const char *content; // Contains element name or text node content
        size_t content_length;
        size_t attributes;
        size_t nesting_level;
        size_t attributes_count;
        enum NodeType {
            NODE_TYPE_DOCUMENT,
            NODE_TYPE_COMMENT,
            NODE_TYPE_UNCLOSED_ELEMENT,
            NODE_TYPE_DOCTYPE,
            NODE_TYPE_TEXT,
            NODE_TYPE_CDATA,
            NODE_TYPE_VOID_ELEMENT,
            NODE_TYPE_NONVOID_ELEMENT,
        } __attribute__((packed)) type;
    } __attribute__((packed)) *nodes;
    struct Attribute {
        const char *name;
        const char *value;
        size_t name_length;
        size_t value_length;
    } *attributes;
    size_t html_strlen;

    // Used to store decoded values in the selector filter. This enables to avoid `malloc` calls in
    // `Selector_filter`.

    char *largest_value_buffer;

    bool has_malloc_error;
};

static const ptrdiff_t POSITION_NOT_STARTED = -1;
static const ptrdiff_t POSITION_EXHAUSTED = -2;

enum SelectorItemType {
    AXIS_NTH,
    AXIS_CHILD,
    AXIS_ANCESTOR,
    AXIS_DESCENDANT,
    AXIS_PRECEDING_SIBLING,
    AXIS_FOLLOWING_SIBLING,

    FILTER_OR,
    FILTER_NOT,
    FILTER_AND,
    FILTER_CASE_I,
    FILTER_NODE_NAME,
    FILTER_ATTRIBUTE_EXISTS,
    FILTER_ATTRIBUTE_EQUALS,
    FILTER_ATTRIBUTE_EQUALS_I,
    FILTER_ATTRIBUTE_CONTAINS,
    FILTER_ATTRIBUTE_CONTAINS_I,
    FILTER_ATTRIBUTE_CONTAINS_WORD,
    FILTER_ATTRIBUTE_CONTAINS_WORD_I,
    FILTER_ATTRIBUTE_STARTS_WITH,
    FILTER_ATTRIBUTE_STARTS_WITH_I,
};

#define SELECTOR_ITEM_TYPE_IS_FILTER(type) ((type) >= FILTER_OR)

struct Selector {
    struct HtmlDocument *doc;
    struct Node *reference_node;
    int_fast8_t active_axis;
    struct SelectorItem {
        union {
            struct {
                ptrdiff_t position;
                size_t axis_n;
            };
            struct {
                const void *arg1;
                const void *arg2;
                size_t arg1_strlen; // Provides a performance boost
            } filter_data;
        };
        enum SelectorItemType type;
    } items[128];
    unsigned char item_count;
};

/*****************************************************************************/
/* `HtmlDocument` */

static bool parse_attribute(struct Attribute *attribute, const char **html_ptr)
{
    const char *html = *html_ptr;
    while (CHARMASK_WHITESPACE[(unsigned char) *html]) {
        html += 1;
    }
    if (*html == '>' || *html == '\0' || *html == '/' && html[1] == '>') {
        *html_ptr = html;
        return false;
    }
    attribute->name = html;
    attribute->name_length = 0;
    attribute->value_length = 0;
    do {
        attribute->name_length += 1;
        html += 1;
    } while (CHARMASK_ATTRIBUTE_NAME_END[(unsigned char) *html] == 0);
    while (CHARMASK_WHITESPACE[(unsigned char) *html]) {
        html += 1;
    }
    if (*html != '=') {
        attribute->value = html;
        *html_ptr = html;
        return true;
    }
    do {
        html += 1;
    } while (CHARMASK_WHITESPACE[(unsigned char) *html]);
    if (*html == '"' || *html == '\'') {
        char quote = *html;
        html += 1;
        attribute->value = html;
        while (*html != '\0' && *html != quote) {
            attribute->value_length += 1;
            html += 1;
        }
        if (*html == quote) {
            html += 1;
        }
    }
    else {
        attribute->value = html;
        while (CHARMASK_ATTRIBUTE_VALUE_END[(unsigned char) *html] == 0) {
            attribute->value_length += 1;
            html += 1;
        }
    }
    while (CHARMASK_WHITESPACE[(unsigned char) *html]) {
        html += 1;
    }
    *html_ptr = html;
    return true;
}

#define CHARSEQICMP(s1, length, s2) (length != sizeof s2 - 1 || strnicmp(s1, s2, length))

struct String HtmlDocument_extract_charset(const char *html)
{
    while (true) {
        if (*html == '\0') {
            break;
        }
        if (html[0] == '<' && html[1] == '!') {
            if (html[2] == '-' && html[3] == '-') {
                html += 4;
                while (
                    *html != '\0' &&
                    (*html != '-' || html[1] != '-' || html[2] != '>')
                ) {
                    html += 1;
                }
            }
            else {
                html += 2;
                while (*html != '>' && *html != '\0') {
                    html += 1;
                }
            }
            if (html - html > 1024 || *html == '\0') {
                break;
            }
        }
        if (*html == '<') {
            html += 1;
            const char *name = html;
            size_t name_length = 0;
            while (CHARMASK_VALID_TAG_NAME[(unsigned char) html[name_length]] == 0) {
                name_length += 1;
            }
            if (!CHARSEQICMP(name, name_length, "script") ||
                !CHARSEQICMP(name, name_length, "style") ||
                !CHARSEQICMP(name, name_length, "title") ||
                !CHARSEQICMP(name, name_length, "textarea"))
            {
                html += name_length;
                do {
                    html += 1;
                } while (
                    *html != '\0' && (*html != '<' || *(html + 1) != '/' ||
                    strnicmp(&html[2], name, name_length))
                );
            }
        }
        if (!strnicmp(html, "<meta", sizeof "<meta" - 1)) {
            html += 1;
            if (html - html > 1024) {
                break;
            }
            continue;
        }
        html += sizeof "<meta" - 1;
        bool has_http_equiv_content_type = false;
        char *content = NULL;
        size_t content_length;
        struct Attribute attr;
        while (parse_attribute(&attr, &html)) {
            if (!strnicmp(attr.name, "charset", attr.name_length)) {
                return entities_to_utf8_malloc(attr.value, attr.value_length, false);
            }
            if (!strnicmp(attr.name, "content", attr.name_length)) {
                content = (char *) attr.value;
                content_length = attr.value_length;
            }
            else if (!strnicmp(attr.name, "http-equiv", attr.name_length)) {
                struct String buffer = entities_to_utf8_malloc(
                    attr.value, attr.value_length, false
                );
                if (!strnicmp(buffer.data, "content-type", buffer.length)) {
                    has_http_equiv_content_type = true;
                }
                String_free(buffer);
            }
        }
        if (has_http_equiv_content_type && content != NULL) {
            char *buffer = malloc(content_length);
            if (buffer == NULL) {
                return NULL_STRING;
            }
            content_length = entities_to_utf8(content, content_length, buffer, false);
            content = buffer;

            size_t charset_begin = 0, charset_length = 0;
            for (; charset_begin < content_length; ++charset_begin) {
                if (content[charset_begin] != ';') {
                    continue;
                }
                do {
                    charset_begin += 1;
                } while (CHARMASK_WHITESPACE[(unsigned char) content[charset_begin]]);
                if (strncmp(&content[charset_begin], "charset", sizeof "charset" - 1)) {
                    continue;
                }
                unsigned char charset_delim = content[charset_begin + sizeof "charset" - 1];
                if (charset_delim != '=' && !CHARMASK_WHITESPACE[(unsigned char) charset_delim]) {
                    continue;
                }
                charset_begin += sizeof "charset" - 1;
                while (CHARMASK_WHITESPACE[(unsigned char) content[charset_begin]]) {
                    charset_begin += 1;
                }
                if (content[charset_begin] != '=') {
                    continue;
                }
                do {
                    charset_begin += 1;
                } while (CHARMASK_WHITESPACE[(unsigned char) content[charset_begin]]);
                if (content[charset_begin] == '"') {
                    // Quotes around charset are valid: https://www.ietf.org/rfc/rfc2045.txt
                    charset_begin += 1;
                }
                while (
                    charset_begin + charset_length < content_length &&
                    !CHARMASK_WHITESPACE[(unsigned char) content[charset_begin + charset_length]] &&
                    content[charset_begin + charset_length] != ';'&&
                    content[charset_begin + charset_length] != '"'
                ) {
                    charset_length += 1;
                }
                break;
            }
            struct String result = {malloc(charset_length), charset_length, true};
            if (result.data == NULL) {
                free(content);
                return NULL_STRING;
            }
            memcpy(result.data, &content[charset_begin], charset_length);
            free(content);
            return result;
        }
    }
    return NULL_STRING;
}

void HtmlDocument_free(struct HtmlDocument *doc)
{
    if (doc->attributes != NULL) {
        free(doc->attributes);
    }
    if (doc->largest_value_buffer != NULL) {
        free(doc->largest_value_buffer);
    }
    free(doc->nodes);
    free(doc);
}

static struct HtmlDocument * HtmlDocument(const char *html, size_t html_strlen)
{
    // Minimizing the number of `realloc` calls is essential to achieve the best performance. We
    // use heuristic starting values depending on the input length. `strlen` is very fast.
    // `*_capacity` must be greater than zero to avoid invalid memory write operations.

    size_t nodes_capacity = 100 + html_strlen / 40;
    size_t attributes_capacity = 100 + nodes_capacity * 2;

    struct HtmlDocument *doc = malloc(sizeof (struct HtmlDocument));
    if (doc == NULL) {
        free(doc);
        return NULL;
    }
    doc->nodes = malloc(nodes_capacity * sizeof (struct Node));
    if (doc->nodes == NULL) {
        free(doc);
        return NULL;
    }
    doc->attributes = malloc(attributes_capacity * sizeof (struct Attribute));
    if (doc->attributes == NULL) {
        free(doc->nodes);
        free(doc);
        return NULL;
    }

    // We cannot use `struct Node *` pointers because `realloc` may break them
    size_t unclosed_elements_size = 0;
    size_t unclosed_elements_capacity = 100;
    size_t *unclosed_elements = malloc(unclosed_elements_capacity * sizeof *unclosed_elements);
    if (unclosed_elements == NULL) {
        free(doc->nodes);
        free(doc);
        return NULL;
    }
    #define INCREMENT_UNCLOSED_ELEMENTS_SIZE() \
        if (++unclosed_elements_size == unclosed_elements_capacity - 1) { \
            unclosed_elements_capacity += 100; \
            size_t *new_unclosed_elements = realloc(unclosed_elements, \
                unclosed_elements_capacity * sizeof *unclosed_elements); \
            if (new_unclosed_elements == NULL) { \
                free(unclosed_elements); \
                HtmlDocument_free(doc); \
                return NULL; \
            } \
            unclosed_elements = new_unclosed_elements; \
        }

    doc->nodes[0] = (struct Node) {
        .content = "#document",
        .content_length = sizeof "#document" - 1,
        .type = NODE_TYPE_DOCUMENT
    };
    doc->node_count = 1;
    doc->html = html;
    doc->html_strlen = html_strlen;
    doc->largest_value_buffer = NULL;
    doc->has_malloc_error = false;

    size_t attributes_count = 0;
    ptrdiff_t html_node = -1, head_node = -1, body_node = -1, tbody_node = -2, colgroup_node = -1;

    // Optimized standard library functions such as strchr and strpbrk traverse the string word for
    // word and not byte for byte. But called in a loop, they are slower because of the overhead of
    // calculating the bitmasks in every call.

    #define INCREMENT_NODE_COUNT() \
        if (++doc->node_count == nodes_capacity - 1) { \
            nodes_capacity = 1 + (size_t) (nodes_capacity * 1.2); \
            struct Node *new_nodes = realloc(doc->nodes, nodes_capacity * sizeof *new_nodes); \
            if (new_nodes == NULL) { \
                free(unclosed_elements); \
                HtmlDocument_free(doc); \
                return NULL; \
            } \
            doc->nodes = new_nodes; \
        }

    size_t largest_value_length = 0;
    while (true) {
        size_t text_node_length = 0;
        bool has_only_whitespace = true;
        if (*html == '<') {
            if (html[1] == '!') {
                const char *comment;
                size_t comment_length;
                if (html[2] == '-' && html[3] == '-') {
                    html += 4;
                    comment = html;
                    while (html[0] != '\0' && (html[0] != '-' || html[1] != '-' || html[2] != '>')) {
                        html += 1;
                    }
                    comment_length = html - comment;
                    html += 3 * (*html != '\0');
                }
                else { // Parser error: `incorrectly-opened-comment`
                    html += 2;
                    comment = html;
                    while (*html != '>' && *html != '\0') {
                        html += 1;
                    }
                    comment_length = html - comment;
                    html += (*html != '\0');
                }
                doc->nodes[doc->node_count] = (struct Node) {
                    .content = comment,
                    .content_length = comment_length,
                    .type = NODE_TYPE_COMMENT,
                    .nesting_level = 1,
                };
                INCREMENT_NODE_COUNT();
            }
            else if (html[1] == '/') {
                html += 2;
                if (!CHARMASK_VALID_TAG_NAME_START[(unsigned char) *html]) {
                    // Handling `invalid-first-character-of-tag-name` of the W3C standard
                    const char *comment = html;
                    while (*html != '>' && *html != '\0') {
                        html += 1;
                    }
                    doc->nodes[doc->node_count] = (struct Node) {
                        .content = comment,
                        .content_length = html - comment,
                        .type = NODE_TYPE_COMMENT,
                        .nesting_level = 1,
                    };
                    INCREMENT_NODE_COUNT();
                    html += (*html != '\0');
                    continue;
                }
                size_t name_length = 0;
                while (CHARMASK_VALID_TAG_NAME[(unsigned char) html[name_length]]) {
                    name_length += 1;
                }

                bool has_found_node = false;
                struct Node *node;
                size_t k = unclosed_elements_size;
                while (k-- > 0) {
                    node = &doc->nodes[unclosed_elements[k]];
                    if (name_length == node->content_length && !strnicmp(node->content, html, name_length)) {
                        has_found_node = true;
                        break;
                    }
                }
                if (has_found_node) {
                    // Here we close all unclosed nodes between the matching start node and the last node.
                    // Example:
                    // <a>
                    // <b>  ← indent_width = 1
                    // text ← indent_width = 2
                    // <c>  ← indent_width = 2
                    // </a>
                    size_t indent_width = unclosed_elements_size - k;
                    size_t node_index = doc->node_count;
                    while (node_index-- > unclosed_elements[k]) {
                        if (node_index == unclosed_elements[unclosed_elements_size - 1]) {
                            unclosed_elements_size -= 1;
                            indent_width -= 1;
                            doc->nodes[node_index].type = NODE_TYPE_NONVOID_ELEMENT;
                        }
                        doc->nodes[node_index].nesting_level += indent_width;
                    }
                }
                html += name_length;
                while (*html != '>' && *html != '\0') {
                    html += 1;
                }
                html += (*html != '\0');
                if (has_found_node || *html == '\0') {
                    continue;
                }

                // Not start tag found. We extend the current text node until the next `<`
                // following the stray tag. Stray tags are filtered out by the
                // `entities_to_utf8` function.

                node = &doc->nodes[doc->node_count - 1];
                if (node->type != NODE_TYPE_TEXT) {
                    continue;
                }
                while (*html != '<' && *html != '\0') {
                    html += 1;
                }
                node->content_length = html - node->content;
            }
            else if (CHARMASK_VALID_TAG_NAME_START[(unsigned char) html[1]]) {
                // Here we analyse a start tag. We use a loop to add nodes because we may need
                // to consider one or multiple optional start tags that are not encoded.

                html += 1;
                const char *name = html;
                size_t name_length = 0;
                size_t new_attributes_count = attributes_count;

                while (CHARMASK_VALID_TAG_NAME[(unsigned char) html[name_length]]) {
                    name_length += 1;
                }
                html += name_length;
                while (parse_attribute(&doc->attributes[new_attributes_count], &html)) {
                    if (doc->attributes[new_attributes_count].value_length > largest_value_length) {
                        largest_value_length = doc->attributes[new_attributes_count].value_length;
                    }
                    if (++new_attributes_count == attributes_capacity) {
                        attributes_capacity *= 1.2;
                        struct Attribute *new_attributes = realloc(
                            doc->attributes, attributes_capacity * sizeof *doc->attributes
                        );
                        if (new_attributes == NULL) {
                            free(unclosed_elements);
                            HtmlDocument_free(doc);
                            return NULL;
                        }
                        doc->attributes = new_attributes;
                    }
                }
                html += (*html == '/');
                html += 1;  // Skipping over `>`

                bool break_after_adding_node = false;
                do {
                    struct Node added_node, *node_for_attributes = NULL;

                    if (!CHARSEQICMP(name, name_length, "!DOCTYPE")) {
                        break;
                    }
                    else if (!CHARSEQICMP(name, name_length, "html")) {
                        if (html_node != -1) {
                            added_node.content = NULL;
                            node_for_attributes = &doc->nodes[html_node];
                        }
                        else {
                            html_node = doc->node_count;
                            added_node = (struct Node) {"html", sizeof "html" - 1};
                            break_after_adding_node = true;
                            node_for_attributes = &added_node;
                        }
                    }
                    else if (html_node == -1) {
                        html_node = doc->node_count;
                        added_node = (struct Node) {"html", sizeof "html" - 1};
                    }
                    else if (!CHARSEQICMP(name, name_length, "head")) {
                        if (head_node != -1) {
                            added_node.content = NULL;
                            node_for_attributes = &doc->nodes[head_node];
                        }
                        else {
                            head_node = doc->node_count;
                            added_node = (struct Node) {"head", sizeof "head" - 1};
                            break_after_adding_node = true;
                            node_for_attributes = &added_node;
                        }
                    }
                    else if (head_node == -1) {
                        head_node = doc->node_count;
                        added_node = (struct Node) {"head", sizeof "head" - 1};
                    }
                    else if (!CHARSEQICMP(name, name_length, "body")) {
                        if (body_node != -1) {
                            added_node.content = NULL;
                            node_for_attributes = &doc->nodes[body_node];
                        }
                        else {
                            body_node = doc->node_count;
                            added_node = (struct Node) {"body", sizeof "body" - 1};
                            break_after_adding_node = true;
                            node_for_attributes = &added_node;
                        }
                    }
                    else if (body_node == -1 &&
                        (CHARSEQICMP(name, name_length, "title") &&
                        CHARSEQICMP(name, name_length, "style") &&
                        CHARSEQICMP(name, name_length, "html") &&
                        CHARSEQICMP(name, name_length, "head") &&
                        CHARSEQICMP(name, name_length, "meta") &&
                        CHARSEQICMP(name, name_length, "base") &&
                        CHARSEQICMP(name, name_length, "link") &&
                        CHARSEQICMP(name, name_length, "script") &&
                        CHARSEQICMP(name, name_length, "noscript")))
                    {
                        body_node = doc->node_count;
                        added_node = (struct Node) {"body", sizeof "body" - 1};
                    }
                    else if (tbody_node == -1 &&
                        (CHARSEQICMP(name, name_length, "caption") ||
                        CHARSEQICMP(name, name_length, "tbody") ||
                        CHARSEQICMP(name, name_length, "colgroup") ||
                        CHARSEQICMP(name, name_length, "thead")))
                    {
                        tbody_node = doc->node_count;
                        added_node = (struct Node) {"tbody", sizeof "tbody" - 1};
                    }
                    else if (colgroup_node == -1 && !CHARSEQICMP(name, name_length, "col")) {
                        colgroup_node = doc->node_count;
                        added_node = (struct Node) {"colgroup", sizeof "colgroup" - 1};
                    }
                    else {
                        if (!CHARSEQICMP(name, name_length, "table")) {
                            tbody_node = -1;
                        }
                        else if (!CHARSEQICMP(name, name_length, "colgroup")) {
                            colgroup_node = doc->node_count;
                        }
                        else {
                            colgroup_node = -1;
                        }
                        added_node = (struct Node) {name, name_length};
                        node_for_attributes = &added_node;
                        break_after_adding_node = true;
                    }

                    /*****************************************************************************/

                    if (node_for_attributes != NULL) {
                        node_for_attributes->attributes = attributes_count;
                        node_for_attributes->attributes_count = new_attributes_count - attributes_count;
                        attributes_count = new_attributes_count;
                    }
                    else {
                        added_node.attributes_count = 0;
                    }

                    if (added_node.content == NULL) {
                        break;
                    }

                    added_node.nesting_level = 1;
                    added_node.type = NODE_TYPE_UNCLOSED_ELEMENT;

                    // Using long if conditions is much faster than looping through data tables
                    // for the following tag-specific logic.

                    // Void elements
                    // https://html.spec.whatwg.org/multipage/syntax.html#void-elements

                    if (!CHARSEQICMP(added_node.content, added_node.content_length, "br") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "img") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "meta") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "link") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "input") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "embed") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "base") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "hr") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "col") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "area") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "wbr") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "source") ||
                        !CHARSEQICMP(added_node.content, added_node.content_length, "track"))
                    {
                        added_node.type = NODE_TYPE_VOID_ELEMENT;
                    }

                    // Auto-close unclosed nodes with optional end tag
                    // https://html.spec.whatwg.org/multipage/syntax.html#optional-tags

                    struct Node *node = unclosed_elements_size == 0 ? NULL :
                        &doc->nodes[unclosed_elements[unclosed_elements_size - 1]];

                    if (node != NULL && (
                        !CHARSEQICMP(added_node.content, added_node.content_length, "body") &&
                        !CHARSEQICMP(node->content, node->content_length, "head") ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "li") &&
                        !CHARSEQICMP(node->content, node->content_length, "li") ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "option") &&
                        !CHARSEQICMP(node->content, node->content_length, "option") ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "thead") &&
                        !CHARSEQICMP(node->content, node->content_length, "colgroup") ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "thead") &&
                        !CHARSEQICMP(node->content, node->content_length, "colgroup") ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "tbody") &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "colgroup") ||
                            !CHARSEQICMP(node->content, node->content_length, "thead")
                        ) ||

                        !CHARSEQICMP(added_node.content, added_node.content_length, "tfoot") &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "colgroup") ||
                            !CHARSEQICMP(node->content, node->content_length, "thead") ||
                            !CHARSEQICMP(node->content, node->content_length, "tbody")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.content, added_node.content_length, "td") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "th")
                        ) &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "td") ||
                            !CHARSEQICMP(node->content, node->content_length, "th")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.content, added_node.content_length, "dt") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "dd")
                        ) &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "dt") ||
                            !CHARSEQICMP(node->content, node->content_length, "dd")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.content, added_node.content_length, "rt") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "rp")
                        ) &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "rt") ||
                            !CHARSEQICMP(node->content, node->content_length, "rp")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.content, added_node.content_length, "optgroup") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "hr")
                        ) &&
                        (
                            !CHARSEQICMP(node->content, node->content_length, "optgroup") ||
                            !CHARSEQICMP(node->content, node->content_length, "option")
                        ) ||

                        !CHARSEQICMP(node->content, node->content_length, "p") &&
                        (
                            !CHARSEQICMP(added_node.content, added_node.content_length, "address") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "article") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "aside") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "blockquote") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "details") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "div") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "dl") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "fieldset") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "figcaption") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "figure") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "footer") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "form") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h1") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h2") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h3") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h4") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h5") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "h6") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "header") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "hgroup") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "hr") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "main") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "menu") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "nav") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "ol") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "p") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "pre") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "search") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "section") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "table") ||
                            !CHARSEQICMP(added_node.content, added_node.content_length, "ul")
                        )))
                    {
                        node->type = NODE_TYPE_NONVOID_ELEMENT;
                        while (++node < &doc->nodes[doc->node_count]) {
                            node->nesting_level += 1;
                        }
                        unclosed_elements_size -= 1;
                    }

                    // Append the node

                    if (added_node.type == NODE_TYPE_UNCLOSED_ELEMENT) {
                        unclosed_elements[unclosed_elements_size] = doc->node_count;
                        INCREMENT_UNCLOSED_ELEMENTS_SIZE();
                    }
                    doc->nodes[doc->node_count] = added_node;
                    INCREMENT_NODE_COUNT();
                } while (!break_after_adding_node);
            }
            else {
                // This will cause the `<` character to be added to a text node
                text_node_length = 1;
                has_only_whitespace = false;
            }
        }
        if (*html == '\0') {
            break;
        }

        enum NodeType type = NODE_TYPE_TEXT;

        struct Node *node = &doc->nodes[doc->node_count - 1];
        if (node->type == NODE_TYPE_UNCLOSED_ELEMENT &&
            (!CHARSEQICMP(node->content, node->content_length, "script") ||
            !CHARSEQICMP(node->content, node->content_length, "style") ||
            !CHARSEQICMP(node->content, node->content_length, "title") ||
            !CHARSEQICMP(node->content, node->content_length, "textarea")))
        {
            type = NODE_TYPE_CDATA;
            while (
                html[text_node_length] != '\0' &&
                (html[text_node_length] != '<' || html[text_node_length + 1] != '/' ||
                strnicmp(&html[text_node_length + 2], node->content, node->content_length))
            ) {
                text_node_length += 1;
            }
        }

        if (type == NODE_TYPE_TEXT) {
            while (html[text_node_length] != '<' && html[text_node_length] != '\0') {
                has_only_whitespace &= CHARMASK_WHITESPACE[(unsigned char) html[text_node_length]];
                text_node_length += 1;
            }
            if (node->type == NODE_TYPE_TEXT) {
                // Example: `a<body>b` -> `<body>ab</body>`;`<body>` between `a` and
                // `b` is a skipped stray tag
                node->content_length = &html[text_node_length] - node->content;
                html += text_node_length;
                continue;
            }
        }

        if (text_node_length == 0) {
            continue;
        }

        if (type == NODE_TYPE_TEXT && !has_only_whitespace && body_node == -1) {
            if (html_node == -1) {
                doc->nodes[doc->node_count] = (struct Node) {
                    .content = "html",
                    .content_length = sizeof "html" - 1,
                    .type = NODE_TYPE_UNCLOSED_ELEMENT,
                    .nesting_level = 1,
                };
                html_node = doc->node_count;
                INCREMENT_NODE_COUNT();
                unclosed_elements[unclosed_elements_size] = html_node;
                INCREMENT_UNCLOSED_ELEMENTS_SIZE();
            }
            if (head_node == -1) {
                doc->nodes[doc->node_count] = (struct Node) {
                    .content = "head",
                    .content_length = sizeof "head" - 1,
                    .type = NODE_TYPE_NONVOID_ELEMENT,
                    .nesting_level = 1,
                };
                head_node = doc->node_count;
                INCREMENT_NODE_COUNT();
            }
            else {
                doc->nodes[head_node].type = NODE_TYPE_NONVOID_ELEMENT;
                for (size_t i = head_node + 1; i < doc->node_count - 1; ++i) {
                    doc->nodes[i].nesting_level += 1;
                }
                while (unclosed_elements[unclosed_elements_size - 1] != head_node) {
                    unclosed_elements_size -= 1;
                }
                unclosed_elements_size -= 1;
            }
            doc->nodes[doc->node_count] = (struct Node) {
                .content = "body",
                .content_length = sizeof "body" - 1,
                .type = NODE_TYPE_UNCLOSED_ELEMENT,
                .nesting_level = 1,
            };
            body_node = doc->node_count;
            INCREMENT_NODE_COUNT();
            unclosed_elements[unclosed_elements_size] = body_node;
            INCREMENT_UNCLOSED_ELEMENTS_SIZE();
        }
        if (type == NODE_TYPE_CDATA || !has_only_whitespace || body_node != -1) {
            doc->nodes[doc->node_count] = (struct Node) {
                .type = type,
                .content = html,
                .content_length = text_node_length,
                .nesting_level = 1,
            };
            INCREMENT_NODE_COUNT();
        }
        html += text_node_length;
    }

    // Next we close all unclosed elements

    struct Node *node = &doc->nodes[doc->node_count - 1];
    while (unclosed_elements_size > 0) {
        if (node == &doc->nodes[unclosed_elements[unclosed_elements_size - 1]]) {
            node->type = NODE_TYPE_NONVOID_ELEMENT;
            unclosed_elements_size -= 1;
        }
        node->nesting_level += unclosed_elements_size;
        node -= 1;
    }

    // We don't reallocate the data structures to smaller sizes (max. saving ~ 20%) because it can
    // cost a lot of performance. It would be very unsual to have many `HtmlDocument` structures
    // allocated at the same time and the memory consumption in general isn't that high - we need
    // only additional 3 MB to store the nodes and attributes of a huge 1.3 MB big test document.

    free(unclosed_elements);

    if (attributes_count == 0) {
        free(doc->attributes);
        doc->attributes = NULL;
    }

    doc->largest_value_buffer = malloc(largest_value_length);
    if (doc->largest_value_buffer == NULL) {
        HtmlDocument_free(doc);
        return NULL;
    }

    return doc;
}

struct String HtmlDocument_get_name(struct HtmlDocument *doc, ptrdiff_t node)
{
    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    if (doc->nodes[node].type == NODE_TYPE_TEXT || doc->nodes[node].type == NODE_TYPE_CDATA) {
        return (struct String) {"#text", sizeof "#text" - 1, false};
    }
    if (doc->nodes[node].type == NODE_TYPE_COMMENT) {
        return (struct String) {"#comment", sizeof "#comment" - 1, false};
    }
    char *name = malloc(doc->nodes[node].content_length);
    if (name == NULL) {
        doc->has_malloc_error = true;
        return NULL_STRING;
    }
    for (size_t i = 0; i < doc->nodes[node].content_length; ++i) {
        name[i] = tolower(doc->nodes[node].content[i]);
    }
    return (struct String) {name, doc->nodes[node].content_length, true};
}

struct String HtmlDocument_get_value(struct HtmlDocument *doc, ptrdiff_t node)
{
    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    struct Node *n = &doc->nodes[node];
    if (n->type == NODE_TYPE_CDATA || n->type == NODE_TYPE_COMMENT) {
        return (struct String) {(char *) n->content, n->content_length, false};
    }
    if (n->type == NODE_TYPE_TEXT) {
        struct String result = entities_to_utf8_malloc(n->content, n->content_length, true);
        if (result.data == NULL) {
            doc->has_malloc_error = true;
        }
        return result;
    }
    return NULL_STRING;
}

struct String HtmlDocument_get_attribute(struct HtmlDocument *doc, ptrdiff_t node, const char *attribute)
{
    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    size_t strlen_attribute = strlen(attribute);
    struct Attribute *attributes = &doc->attributes[doc->nodes[node].attributes];
    for (size_t i = 0; i < doc->nodes[node].attributes_count; ++i) {
        if (attributes[i].name_length == strlen_attribute &&
            !strnicmp(attributes[i].name, attribute, attributes[i].name_length))
        {
            struct String result =
                entities_to_utf8_malloc(attributes[i].value, attributes[i].value_length, false);
            if (result.data == NULL) {
                doc->has_malloc_error = true;
            }
            return result;
        }
    }
    return NULL_STRING;
}

static size_t get_escape_length(const char *html, size_t length, bool is_attribute)
{
    size_t escape_length = length, i = length;
    while (i-- > 0) {
        if (!is_attribute && html[i] == '<') {
            escape_length += sizeof "&lt;" - 2;
        }
        else if (!is_attribute && html[i] == '>') {
            escape_length += sizeof "&gt;" - 2;
        }
        else if (html[i] == '&') {
            escape_length += sizeof "&amp;" - 2;
        }
        else if (is_attribute && html[i] == '"') {
            escape_length += sizeof "&quot;" - 2;
        }
        else if (html[i] == 0xA0 && i > 0 && html[i - 1] == 0xC2) {
            escape_length += sizeof "&nbsp;" - 3;
            i -= 1;
        }
    }
    return escape_length;
}

static void escape_inplace(char *input, size_t input_length, size_t escape_length, bool is_attribute)
{
    // We exploit the fact that the escaped string will never be smaller than
    // the input. This makes it possible to rewrite the input in-place from its end.
    //
    // https://dev.w3.org/html5/spec-LC/the-end.html#html-fragment-serialization-algorithm
    // Section: “Escaping a string”

    if (input_length == escape_length) {
        return;
    }
    size_t e = escape_length - 1;
    size_t i = input_length;
    while (i-- > 0) {
        if (!is_attribute && input[i] == '<') {
            input[e--] = ';';
            input[e--] = 't';
            input[e--] = 'l';
            input[e--] = '&';
        }
        else if (!is_attribute && input[i] == '>') {
            input[e--] = ';';
            input[e--] = 't';
            input[e--] = 'g';
            input[e--] = '&';
        }
        else if (input[i] == '&') {
            input[e--] = ';';
            input[e--] = 'p';
            input[e--] = 'm';
            input[e--] = 'a';
            input[e--] = '&';
        }
        else if (is_attribute && input[i] == '"') {
            input[e--] = ';';
            input[e--] = 't';
            input[e--] = 'o';
            input[e--] = 'u';
            input[e--] = 'q';
            input[e--] = '&';
        }
        else if (input[i] == 0xA0 && i > 0 && input[i - 1] == 0xC2) {
            input[e--] = ';';
            input[e--] = 'p';
            input[e--] = 's';
            input[e--] = 'b';
            input[e--] = 'n';
            input[e--] = '&';
            i -= 1;
        }
        else {
            input[e--] = input[i];
        }
    }
}

struct String HtmlDocument_get_html(struct HtmlDocument *doc, ptrdiff_t node, bool inner)
{
    // https://dev.w3.org/html5/spec-LC/the-end.html#html-fragment-serialization-algorithm
    //
    // “For HTML elements created by the HTML parser […], tagname will be lowercase.”
    //
    // “For attributes on HTML elements set by the HTML parser […], the local name will be
    // lowercase.”

    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    size_t result_capacity = doc->html_strlen;
    struct String result = {malloc(result_capacity), 0, true};
    if (result.data == NULL) {
        return NULL_STRING;
    }

    #define EXTEND(_length) \
        if (result.length + _length >= result_capacity) { \
            result_capacity += _length + 1024; \
            char *r = realloc(result.data, result_capacity); \
            if (r == NULL) { \
                doc->has_malloc_error = true; \
                free(result.data); \
                return NULL_STRING; \
            } \
            result.data = r; \
        }

    if (node == 0) {
        inner = true;
    }
    const struct Node *last_node = &doc->nodes[doc->node_count - 1];
    for (struct Node *n = &doc->nodes[node + inner];
        n <= last_node &&
        (n == &doc->nodes[node] || n->nesting_level > doc->nodes[node].nesting_level);
        ++n)
    {
        if (n->type == NODE_TYPE_COMMENT) {
            EXTEND(4 + n->content_length + 3);
            result.data[result.length++] = '<';
            result.data[result.length++] = '!';
            result.data[result.length++] = '-';
            result.data[result.length++] = '-';
            memcpy(&result.data[result.length], n->content, n->content_length);
            result.length += n->content_length;
            result.data[result.length++] = '-';
            result.data[result.length++] = '-';
            result.data[result.length++] = '>';
        }
        else if (n->type == NODE_TYPE_TEXT) {
            EXTEND(n->content_length);
            size_t utf8_length = entities_to_utf8(n->content, n->content_length,
                &result.data[result.length], true);
            size_t escape_length = get_escape_length(&result.data[result.length], utf8_length, false);
            EXTEND(escape_length);
            escape_inplace(&result.data[result.length], utf8_length, escape_length, false);
            result.length += escape_length;
        }
        else if (n->type == NODE_TYPE_CDATA) {
            EXTEND(n->content_length);
            memcpy(&result.data[result.length], n->content, n->content_length);
            result.length += n->content_length;
        }
        else {
            EXTEND(1 + n->content_length + 1);
            result.data[result.length++] = '<';
            for (size_t i = 0; i < n->content_length; ++i) {
                result.data[result.length++] = tolower(n->content[i]);
            }

            struct Attribute *attribute = &doc->attributes[n->attributes];
            while (attribute < &doc->attributes[n->attributes + n->attributes_count]) {
                EXTEND(1 + attribute->name_length + 2);
                result.data[result.length++] = ' ';
                for (int i = 0; i < attribute->name_length; ++i) {
                    result.data[result.length++] = tolower(attribute->name[i]);
                }
                result.data[result.length++] = '=';
                result.data[result.length++] = '"';

                EXTEND(n->content_length);
                size_t utf8_length = entities_to_utf8(attribute->value, attribute->value_length,
                    &result.data[result.length], false);
                size_t escape_length = get_escape_length(&result.data[result.length], utf8_length, true);
                EXTEND(escape_length);
                escape_inplace(&result.data[result.length], utf8_length, escape_length, true);
                result.length += escape_length;

                EXTEND(1);
                result.data[result.length++] = '"';

                attribute += 1;
            }

            result.data[result.length++] = '>';
        }
        size_t preceding_nesting_level = n->nesting_level;
        size_t next_nesting_level = n == last_node ||
            (n + 1)->nesting_level < doc->nodes[node].nesting_level ?
            doc->nodes[node].nesting_level : (n + 1)->nesting_level;
        if (next_nesting_level <= preceding_nesting_level) {
            struct Node *counterpart = n;
            do {
                if (counterpart->nesting_level == preceding_nesting_level - 1 ||
                    counterpart->nesting_level == preceding_nesting_level &&
                    n->type == NODE_TYPE_NONVOID_ELEMENT)
                {
                    EXTEND(2 + counterpart->content_length + 1);
                    result.data[result.length++] = '<';
                    result.data[result.length++] = '/';
                    for (size_t i = 0; i < counterpart->content_length; ++i) {
                        result.data[result.length++] = tolower(counterpart->content[i]);
                    }
                    result.data[result.length++] = '>';
                    preceding_nesting_level -= 1;
                }
                counterpart -= 1;
                if (inner && counterpart == &doc->nodes[node]) {
                    break;
                }
            } while (preceding_nesting_level > next_nesting_level);
        }
    }
    return result;
}

struct String HtmlDocument_get_inner_html(struct HtmlDocument *doc, ptrdiff_t node)
{
    return HtmlDocument_get_html(doc, node, true);
}

struct String HtmlDocument_get_outer_html(struct HtmlDocument *doc, ptrdiff_t node)
{
    return HtmlDocument_get_html(doc, node, false);
}

bool HtmlDocument_has_malloc_error(struct HtmlDocument *doc)
{
    // If this function returns true, it means that the extracted data is not reliable and must be
    // discarded because `malloc` has failed.
    //
    // When `malloc` fails, the name, attribute or value of a node may be incorrectly returned as
    // NULL.

    return doc->has_malloc_error;
}

struct Selector * HtmlDocument_select(struct HtmlDocument *doc, size_t node)
{
    struct Selector *s = malloc(sizeof (struct Selector));
    if (s == NULL) {
        return NULL;
    }
    s->doc = doc;
    s->item_count = 0;
    s->active_axis = 0;
    s->reference_node = node < doc->node_count ? &doc->nodes[node] : doc->nodes;
    return s;
}

/*****************************************************************************/
/* `Selector` */

static bool str_contains(const char *haystack, size_t haystack_length, const char *needle, bool is_word,
    bool case_i)
{
    int_fast16_t diff;
    for (size_t hi = 0, ni = 0; hi < haystack_length; ++hi) {
        if (is_word && hi > 0 && !CHARMASK_WHITESPACE[(unsigned char) haystack[hi - 1]]) {
            continue;
        }
        if ((diff = haystack[hi] - needle[ni]) && case_i) {
            if ((unsigned char) (haystack[hi] - 'A') <= 'Z' - 'A') {
                diff += 'a' - 'A';
            }
            if ((unsigned char) (needle[ni] - 'A') <= 'Z' - 'A') {
                diff -= 'a' - 'A';
            }
        }
        ni = (diff == 0) * (ni + 1);
        if (needle[ni + 1] == '\0' && (!is_word ||
            CHARMASK_WHITESPACE[(unsigned char) haystack[hi + ni + 1]]))
        {
            return true;
        }
    }
    return false;
}

static void Selector_push_selector(struct Selector *sel, enum SelectorItemType type,
    const void *filter_arg1, const void *filter_arg2, size_t axis_n)
{
    if (sel->item_count == 0 && SELECTOR_ITEM_TYPE_IS_FILTER(type)) {
        return;
    }
    if (sel->item_count == sizeof sel->items / sizeof *sel->items) {
        return;
    }
    sel->items[sel->item_count].type = type;
    if (SELECTOR_ITEM_TYPE_IS_FILTER(type)) {
        sel->items[sel->item_count].filter_data.arg1 = filter_arg1;
        if (type >= FILTER_NODE_NAME) {
            sel->items[sel->item_count].filter_data.arg1_strlen = strlen(filter_arg1);
        }
        sel->items[sel->item_count].filter_data.arg2 = filter_arg2;
    }
    else {
        sel->items[sel->item_count].position = POSITION_NOT_STARTED;
        sel->items[sel->item_count].axis_n = axis_n;
    }
    sel->item_count += 1;
}

static void Selector_iterate_axis(struct Selector *sel, struct SelectorItem *si, const struct Node *ref)
{
    if (si->position == POSITION_NOT_STARTED) {
        si->position = ref - sel->doc->nodes;
    }

    if (si->type == AXIS_NTH) {
        if (si == sel->items) {
            if (si->axis_n != 0) {
                si->position = POSITION_EXHAUSTED;
            }
            return;
        }
        struct SelectorItem *preceding_axis = si;
        do {
            preceding_axis -= 1;
        } while (SELECTOR_ITEM_TYPE_IS_FILTER(preceding_axis->type));
        if (si->axis_n + 1 != preceding_axis->axis_n) {
            si->position = POSITION_EXHAUSTED;
        }
    }
    else if (si->type == AXIS_CHILD) {
        while (si->position++ < sel->doc->node_count - 1) {
            if (sel->doc->nodes[si->position].nesting_level > ref->nesting_level + 1) {
                continue;
            }
            if (sel->doc->nodes[si->position].nesting_level < ref->nesting_level + 1) {
                break;
            }
            return;
        }
        si->position = POSITION_EXHAUSTED;
    }
    else if (si->type == AXIS_ANCESTOR) {
        size_t current_nesting_level = sel->doc->nodes[si->position].nesting_level;
        while (si->position-- > 0) {
            if (sel->doc->nodes[si->position].nesting_level < current_nesting_level) {
                return;
            }
        }
        si->position = POSITION_EXHAUSTED;
    }
    else if (si->type == AXIS_DESCENDANT) {
        if (si->position == sel->doc->node_count - 1 ||
            sel->doc->nodes[++si->position].nesting_level <= ref->nesting_level)
        {
            si->position = POSITION_EXHAUSTED;
        }
    }
    else if (si->type == AXIS_PRECEDING_SIBLING) {
        while (si->position > 0) {
            const struct Node *node = &sel->doc->nodes[--si->position];
            if (node->nesting_level == ref->nesting_level) return;
            if (node->nesting_level < ref->nesting_level) break;
        }
        si->position = POSITION_EXHAUSTED;
    }
    else if (si->type == AXIS_FOLLOWING_SIBLING) {
        while (si->position < sel->doc->node_count - 1) {
            const struct Node *node = &sel->doc->nodes[++si->position];
            if (node->nesting_level == ref->nesting_level) return;
            if (node->nesting_level < ref->nesting_level) break;
        }
        si->position = POSITION_EXHAUSTED;
    }
}

static bool Selector_filter(struct Selector *sel, struct SelectorItem *si, struct Node *node)
{
    if (si->type == FILTER_NODE_NAME) {
        const char *name;
        size_t name_length;
        if (node->type == NODE_TYPE_COMMENT) {
            name = "#comment";
            name_length = sizeof "#comment" - 1;
        }
        else if (node->type == NODE_TYPE_TEXT || node->type == NODE_TYPE_CDATA) {
            name = "#text";
            name_length = sizeof "#text" - 1;
        }
        else {
            name = node->content;
            name_length = node->content_length;
        }
        return name_length == si->filter_data.arg1_strlen &&
            !strnicmp(name, si->filter_data.arg1, name_length);
    }

    struct Attribute *attr_end = &sel->doc->attributes[node->attributes + node->attributes_count];
    for (
        struct Attribute *attr = &sel->doc->attributes[node->attributes];
        attr < attr_end;
        ++attr
    ) {
        if (si->filter_data.arg1_strlen != attr->name_length ||
            strnicmp(si->filter_data.arg1, attr->name, attr->name_length))
        {
            continue;
        }
        if (si->type == FILTER_ATTRIBUTE_EXISTS) {
            return true;
        }
        char *value = sel->doc->largest_value_buffer;
        size_t value_length = entities_to_utf8(attr->value, attr->value_length, value, false);

        bool matches = false;
        if (si->type == FILTER_ATTRIBUTE_EQUALS) {
            matches = value_length == strlen(si->filter_data.arg2) &&
                      !strncmp(si->filter_data.arg2, value, value_length);
        }
        else if (si->type == FILTER_ATTRIBUTE_EQUALS_I) {
            matches = value_length == strlen(si->filter_data.arg2) &&
                      !strnicmp(si->filter_data.arg2, value, value_length);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS) {
            matches = str_contains(value, value_length, si->filter_data.arg2, false, false);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_I) {
            matches = str_contains(value, value_length, si->filter_data.arg2, false, true);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_WORD) {
            matches = str_contains(value, value_length, si->filter_data.arg2, true, false);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_WORD_I) {
            matches = str_contains(value, value_length, si->filter_data.arg2, true, true);
        }
        else if (si->type == FILTER_ATTRIBUTE_STARTS_WITH) {
            matches = !strncmp(si->filter_data.arg2, value, strlen(si->filter_data.arg2));
        }
        else if (si->type == FILTER_ATTRIBUTE_STARTS_WITH_I) {
            matches = !strnicmp(si->filter_data.arg2, value, strlen(si->filter_data.arg2));
        }

        if (matches) {
            return true;
        }
    }
    return false;
}

ptrdiff_t Selector_iterate(struct Selector *sel)
{
    // The logic here relies on the refusal to push filters to selector item position 0

    if (sel->item_count == 0 || sel->items[0].position == POSITION_EXHAUSTED) {
        return -1;
    }
    bool bool_stack[sizeof sel->items / sizeof *sel->items];
    while (true) {
        int_fast8_t preceding_axis = sel->active_axis;
        while (preceding_axis-- > 0) {
            if (!SELECTOR_ITEM_TYPE_IS_FILTER(sel->items[preceding_axis].type)) {
                break;
            }
        }
        const struct Node *ref = preceding_axis == -1 ? sel->reference_node :
            &sel->doc->nodes[sel->items[preceding_axis].position];

        Selector_iterate_axis(sel, &sel->items[sel->active_axis], ref);
        if (sel->items[sel->active_axis].position == POSITION_EXHAUSTED) {
            if (sel->active_axis == 0) {
                return -1;
            }
            do {
                sel->active_axis -= 1;
            } while (
                sel->active_axis > 0 &&
                SELECTOR_ITEM_TYPE_IS_FILTER(sel->items[sel->active_axis].type)
            );
            continue;
        }

        int_fast8_t filter_index = sel->active_axis;
        int_fast8_t bool_stack_size = 0;
        while (
            ++filter_index < sel->item_count &&
            SELECTOR_ITEM_TYPE_IS_FILTER(sel->items[filter_index].type)
        ) {
            if (sel->items[filter_index].type == FILTER_NOT) {
                if (bool_stack_size >= 1) {
                    bool_stack[bool_stack_size - 1] = !bool_stack[bool_stack_size - 1];
                }
            }
            else if (sel->items[filter_index].type == FILTER_AND) {
                if (bool_stack_size >= 2) {
                    bool_stack_size -= 1;
                    bool_stack[bool_stack_size - 1] &= bool_stack[bool_stack_size];
                }
            }
            else if (sel->items[filter_index].type == FILTER_OR) {
                if (bool_stack_size >= 2) {
                    bool_stack_size -= 1;
                    bool_stack[bool_stack_size - 1] |= bool_stack[bool_stack_size];
                }
            }
            else {
                struct Node *node = &sel->doc->nodes[sel->items[sel->active_axis].position];
                bool_stack[bool_stack_size++] = Selector_filter(sel, &sel->items[filter_index], node);
            }
        }
        bool filter_state = true;
        while (bool_stack_size-- > 0) {
            if (bool_stack[bool_stack_size] == false) {
                filter_state = false;
                break;
            }
        }
        if (filter_state == false) {
            continue;
        }

        if (filter_index == sel->item_count) {
            return sel->items[sel->active_axis].position;
        }

        sel->items[sel->active_axis].axis_n += 1;
        sel->active_axis = filter_index;
        sel->items[sel->active_axis].position = POSITION_NOT_STARTED;
        if (sel->items[sel->active_axis].type != AXIS_NTH) {
            sel->items[sel->active_axis].axis_n = 0;
        }
    }
}

void Selector_child(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_CHILD, NULL, NULL, 0);
}

void Selector_ancestor(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_ANCESTOR, NULL, NULL, 0);
}

void Selector_descendant(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_DESCENDANT, NULL, NULL, 0);
}

void Selector_preceding_sibling(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_PRECEDING_SIBLING, NULL, NULL, 0);
}

void Selector_following_sibling(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_FOLLOWING_SIBLING, NULL, NULL, 0);
}

void Selector_nth(struct Selector *sel, size_t n)
{
    Selector_push_selector(sel, AXIS_NTH, NULL, NULL, n);
}

void Selector_name(struct Selector *sel, const char *name)
{
    Selector_push_selector(sel, FILTER_NODE_NAME, name, NULL, 0);
}

void Selector_attribute_exists(struct Selector *sel, const char *name)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_EXISTS, name, NULL, 0);
}

void Selector_attribute_equals(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_EQUALS, name, value, 0);
}

void Selector_attribute_contains(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_CONTAINS, name, value, 0);
}

void Selector_attribute_starts_with(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_STARTS_WITH, name, value, 0);
}

void Selector_or(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_OR, NULL, NULL, 0);
}

void Selector_and(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_AND, NULL, NULL, 0);
}

void Selector_not(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_NOT, NULL, NULL, 0);
}

void Selector_case_i(struct Selector *sel)
{
    if (sel->item_count == 0) {
        return;
    }
    struct SelectorItem *si = &sel->items[sel->item_count - 1];
    if (si->type == FILTER_ATTRIBUTE_EQUALS) {
        si->type = FILTER_ATTRIBUTE_EQUALS_I;
    }
    else if (si->type == FILTER_ATTRIBUTE_CONTAINS) {
        si->type = FILTER_ATTRIBUTE_CONTAINS_I;
    }
    else if (si->type == FILTER_ATTRIBUTE_CONTAINS_WORD) {
        si->type = FILTER_ATTRIBUTE_CONTAINS_WORD_I;
    }
    else if (si->type == FILTER_ATTRIBUTE_STARTS_WITH) {
        si->type = FILTER_ATTRIBUTE_STARTS_WITH_I;
    }
}

void Selector_rewind(struct Selector *sel)
{
    if (sel->item_count > 0) {
        // This is safe because we refuse to push filters to position 0
        sel->items[0].position = POSITION_NOT_STARTED;
    }
    sel->active_axis = 0;
}

void Selector_reset(struct Selector *sel)
{
    sel->active_axis = 0;
    sel->item_count = 0;
}

/*****************************************************************************/
/* IRI resolver */

static uint_fast8_t encode_digit(uint_fast32_t d)
{
    return d + 22 + 75 * (d < 26);
}

enum {BASE = 36, TMIN = 1, TMAX = 26, SKEW = 38, DAMP = 700};

static uint_fast32_t adapt(uint_fast32_t delta, uint_fast32_t numpoints, bool firsttime)
{
    uint_fast32_t k;

    delta = firsttime ? delta / DAMP : delta >> 1;
    delta += delta / numpoints;
    for (k = 0;  delta > ((BASE - TMIN) * TMAX) / 2;  k += BASE) {
        delta /= BASE - TMIN;
    }
    return k + (BASE - TMIN + 1) * delta / (delta + SKEW);
}

static uint_fast8_t from_hex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a';
    if (c >= 'A' && c <= 'F') return c - 'A';
    return -1;
}

struct String resolve_iri(struct String reference, struct String base)
{
    // Resolve UTF-8-encoded IRI references, convert to ASCII-encoded URI format, and normalize the URI.
    //
    // IRI: https://www.rfc-editor.org/rfc/rfc3987
    // URI resolving: https://www.rfc-editor.org/rfc/rfc1808#section-5

    size_t i;
    enum {
        COMPONENT_SCHEME,
        COMPONENT_AUTHORITY,
        COMPONENT_ABSOLUTE_PATH,
        COMPONENT_RELATIVE_PATH,
        COMPONENT_QUERY_STRING,
        COMPONENT_FRAGMENT
    } reference_component;

    if (reference.length >= 2 && reference.data[0] == '/' && reference.data[1] == '/') {
        reference_component = COMPONENT_AUTHORITY;
    }
    else if (reference.length == 0 || reference.data[0] == '#') {
        reference_component = COMPONENT_FRAGMENT;
    }
    else if (reference.data[0] == '/') {
        reference_component = COMPONENT_ABSOLUTE_PATH;
    }
    else if (reference.data[0] == '?') {
        reference_component = COMPONENT_QUERY_STRING;
    }
    else {
        reference_component = COMPONENT_RELATIVE_PATH;
        for (i = 0; i < reference.length; ++i) {
            if (reference.data[i] == '?') {
                break;
            }
            if (reference.data[i] == ':') {
                reference_component = COMPONENT_SCHEME;
                break;
            }
        }
    }

    size_t normalized_capacity = 1024;
    struct String normalized = {malloc(normalized_capacity), 0, true};
    if (normalized.data == NULL) {
        return NULL_STRING;
    }
    #define APPEND(c) \
        if (normalized.length == normalized_capacity) { \
            normalized_capacity += 256; \
            char *r = realloc(normalized.data, normalized_capacity); \
            if (r == NULL) { \
                free(normalized.data); \
                return NULL_STRING; \
            } \
            normalized.data = r; \
        } \
        normalized.data[normalized.length++] = c;

    struct String source = reference_component == COMPONENT_SCHEME ? reference : base;
    i = 0;

    // Copy the scheme from `source` to the result

    size_t scheme_length = 0;
    while (i < source.length && source.data[i] != ':') {
        APPEND(tolower(source.data[i]));
        scheme_length += 1;
        i += 1;
    }
    if (source.data[i] == ':') {
        APPEND(':');
        i += 1;
    }

    // Copy the authority from `source` to the result

    if (reference_component == COMPONENT_AUTHORITY) {
        source = reference;
        i = 0;
    }
    if (i + 1 < source.length && source.data[i] == '/' && source.data[i + 1] == '/') {
        size_t authority_index = i;
        size_t at_index = 0;
        for (i = authority_index + 2; i < source.length && source.data[i] != '/' &&
                source.data[i] != '?' && source.data[i] != '#' && source.data[i] != ':'; ++i)
        {
            if (source.data[i] == '@') {
                at_index = i;
            }
        }
        size_t domain_end = i;
        size_t domain_start = at_index > 0 ? at_index + 1 : authority_index + 2;
        for (i = authority_index; i < domain_start; ++i) {
            APPEND(source.data[i]);
        }

        // Append domain and convert IDN to ASCII
        // Punycode implementation: <https://datatracker.ietf.org/doc/html/rfc3492>

        size_t domain_label_start = domain_start;
        while (true) {
            uint_fast32_t codepoints[63];
            uint_fast8_t num_codepoints = 0;
            uint_fast8_t num_basic_codepoints = 0;
            for (i = domain_label_start; i < domain_end && source.data[i] != '.'; ++i) {
                if (i - domain_label_start >= 63) {
                    // “Each node [of the domain name space] has a label, which is zero to 63
                    // octets in length.” https://datatracker.ietf.org/doc/html/rfc1034#section-3.1

                    free(source.data);
                    return NULL_STRING;
                }
                if ((unsigned char) source.data[i] < 0b10000000) {
                    codepoints[num_codepoints++] = source.data[i];
                    num_basic_codepoints++;
                }
                else if ((unsigned char) source.data[i] < 0b11100000) {
                    if (i + 1 >= domain_end) {
                        return NULL_STRING;
                    }
                    codepoints[num_codepoints++] =
                        ((source.data[i] & 0b00011111) << 6) +
                        (source.data[i + 1] & 0b00111111);
                    i += 1;
                }
                else if ((unsigned char) source.data[i] < 0b11110000) {
                    if (i + 2 >= domain_end) {
                        return NULL_STRING;
                    }
                    codepoints[num_codepoints++] =
                        (source.data[i] & 0b00001111) << 12 +
                        (source.data[i + 1] & 0b00111111) << 6 +
                        (source.data[i + 2] & 0b00111111);
                    i += 2;
                }
                else if ((unsigned char) source.data[i] < 0b11111000) {
                    if (i + 3 >= domain_end) {
                        return NULL_STRING;
                    }
                    codepoints[num_codepoints++] =
                        (source.data[i] & 0b00000111) << 18 +
                        (source.data[i + 1] & 0b00111111) << 12 +
                        (source.data[i + 2] & 0b00111111) << 6 +
                        (source.data[i + 3] & 0b00111111);
                    i += 3;
                }
            }
            if (num_codepoints > num_basic_codepoints) {
                APPEND('x');
                APPEND('n');
                APPEND('-');
                APPEND('-');
            }
            for (i = domain_label_start; i < domain_end && source.data[i] != '.'; ++i) {
                if ((unsigned char) source.data[i] < 128) {
                    APPEND(tolower(source.data[i]));
                }
            }
            domain_label_start = i;
            if (num_codepoints > num_basic_codepoints) {
                APPEND('-');
            }

            uint_fast32_t bias = 72;
            uint_fast32_t next_codepoint, codepoint = 128;
            uint_fast32_t delta = 0;
            uint_fast32_t k, t;
            uint_fast8_t num_handled_codepoints = num_basic_codepoints;
            const uint_fast32_t MAX_INT = -1;

            while (num_handled_codepoints < num_codepoints) {
                for (next_codepoint = MAX_INT, i = 0; i < num_codepoints; ++i) {
                    if (codepoints[i] >= codepoint && codepoints[i] < next_codepoint) {
                        next_codepoint = codepoints[i];
                    }
                }

                if (next_codepoint - codepoint > (MAX_INT - delta) / (num_handled_codepoints + 1)) {
                    // PuncyCode overflow
                    free(source.data);
                    return NULL_STRING;
                }
                delta += (next_codepoint - codepoint) * (num_handled_codepoints + 1);
                codepoint = next_codepoint;

                uint_fast32_t q;
                for (i = 0; i < num_codepoints; ++i) {
                    if (codepoints[i] < codepoint && ++delta == 0) {
                        // PunyCode overflow
                        free(source.data);
                        return NULL_STRING;
                    }
                    if (codepoints[i] == codepoint) {
                        for (q = delta, k = BASE;  ; k += BASE) {
                            t = k <= bias ? TMIN : k >= bias + TMAX ? TMAX : k - bias;
                            if (q < t) {
                                break;
                            }
                            APPEND(encode_digit(t + (q - t) % (BASE - t)));
                            q = (q - t) / (BASE - t);
                        }

                        APPEND(encode_digit(q));
                        bias = adapt(delta, num_handled_codepoints + 1,
                            num_handled_codepoints == num_basic_codepoints);
                        delta = 0;
                        num_handled_codepoints++;
                    }
                }
                ++delta;
                ++codepoint;
            }
            if (source.data[domain_label_start++] != '.') {
                break;
            }
            APPEND('.');
        }
        i = domain_end;

        // Append port

        if (source.data[i] == ':') {
            do {
                i += 1;
            } while (i < source.length && source.data[i] == '0');

            if (i + 1 < source.length && source.data[i] == '8' && source.data[i + 1] == '0' &&
                !strncmp(normalized.data, "http", scheme_length))
            {
                i += 2;
            }
            else if (i + 2 < source.length && source.data[i] == '4' && source.data[i + 1] == '4' &&
                source.data[i + 2] == '3' && !strncmp(normalized.data, "https", scheme_length))
            {
                i += 3;
            }
            else if (i + 1 >= source.length || source.data[i + 1] == '/' || source.data[i + 1] == '?' ||
                source.data[i + 1] == '#')
            {
                // “URI producers and normalizers should omit the ":" delimiter that separates host
                // from port if the port component is empty.”
                // <https://www.rfc-editor.org/rfc/rfc3986#section-3.2>

                i += 1;
            }
            else {
                APPEND(':');
                while (
                    i < source.length && source.data[i] != '/' && source.data[i] != '?' &&
                    source.data[i] != '#'
                ) {
                    if (source.data[i] < '0' || source.data[i] > '9') {
                        free(normalized.data);
                        return NULL_STRING;
                    }
                    APPEND(source.data[i++]);
                }
            }
        }
        APPEND('/');
        if (i < source.length && source.data[i] == '/') {
            i += 1;
        }
    }

    // Copy the path from `source` to the result. When copying from `base`, `cut_off` specifies the
    // index at which to switch to `reference` as the source.

    if (reference_component == COMPONENT_ABSOLUTE_PATH) {
        source = reference;
        i = 1;
    }
    size_t cut_off;
    if (reference_component == COMPONENT_RELATIVE_PATH) {
        cut_off = i;
        while (base.data[cut_off] != '?' && base.data[cut_off] != '#' && cut_off < base.length) {
            cut_off += 1;
        }
        while (cut_off >= i && base.data[cut_off] != '/') {
            cut_off -= 1;
        }
        cut_off += 1;
    }
    else {
        cut_off = -1;
    }
    bool is_in_path = true;
    size_t normalized_path_start = normalized.length - 1;
    while (true) {
        if (i >= source.length) {
            if (source.data != reference.data || source.length != reference.length) {
                source = reference;
                i = 0;
                continue;
            }
            else {
                break;
            }
        }
        else if (source.data == base.data && i == cut_off) {
            source = reference;
            i = 0;
            continue;
        }
        else if (source.data[i] == '?') {
            is_in_path = false;
            if (reference_component == COMPONENT_QUERY_STRING && source.data == base.data) {
                source = reference;
                i = 0;
            }
            APPEND('?');
        }
        else if (source.data[i] == '#') {
            is_in_path = false;
            if (reference_component == COMPONENT_FRAGMENT && source.data == base.data) {
                source = reference;
                i = 0;
            }
            APPEND('#');
        }
        else if (
            is_in_path &&
            normalized.data[normalized.length - 1] == '/' &&
            source.data[i] == '.' &&
            (i == source.length - 1 || source.data[i + 1] == '/' || source.data[i + 1] == '?' ||
             source.data[i + 1] == '#')
        ) {
            i += 2;
            continue;
        }
        else if (
            is_in_path &&
            i + 1 < source.length &&
            normalized.data[normalized.length - 1] == '/' &&
            source.data[i] == '.' && source.data[i + 1] == '.' &&
            (i == source.length - 2 || source.data[i + 2] == '/' || source.data[i + 2] == '?' ||
             source.data[i + 2] == '#')
        ) {
            i += 2;
            if (source.data[i] == '/') {
                i += 1;
            }
            if (normalized.length - 1 == normalized_path_start) {
                continue;
            }
            while (normalized.data[normalized.length] != '/') {
                normalized.length -= 1;
            }
            normalized.length -= 1;
            while (normalized.data[normalized.length - 1] != '/') {
                normalized.length -= 1;
            }
            continue;
        }
        else if (source.data[i] == '%') {
            i += 1;
            if (i + 1 >= source.length) {
                APPEND('%');
                continue;
            }
            uint_fast8_t hex_digit1 = from_hex(source.data[i]);
            if (hex_digit1 < 0) {
                APPEND('%');
                continue;
            }
            uint_fast8_t hex_digit2 = from_hex(source.data[i + 1]);
            if (hex_digit2 < 0) {
                APPEND('%');
                continue;
            }
            unsigned char hex = hex_digit1 * 16 + hex_digit2;
            if (hex >= 'a' && hex <= 'z' || hex >= 'A' && hex <= 'Z' ||
                hex == '-' || hex == '_' || hex == '.' || hex == '~')
            {
                APPEND(hex);
            }
            else {
                // “For consistency, URI producers and normalizers should use uppercase hexadecimal
                // digits for all percent-encodings.” <https://www.rfc-editor.org/rfc/rfc3986#section-2.1>

                APPEND('%');
                APPEND(toupper(source.data[i]));
                APPEND(toupper(source.data[i + 1]));
            }
            i += 1;
        }
        else if ((unsigned char) source.data[i] > 127) {
            APPEND('%');
            unsigned char x;
            x = (unsigned char) source.data[i] >> 4;
            x += x < 10 ? '0' : 'A' - 10;
            APPEND(x);
            x = (unsigned char) source.data[i] & 0b1111;
            x += x < 10 ? '0' : 'A' - 10;
            APPEND(x);
        }
        else {
            APPEND(source.data[i]);
        }
        i += 1;
    }

    char *new_normalized_data = realloc(normalized.data, normalized.length);
    if (new_normalized_data == NULL) {
        free(normalized.data);
        return NULL_STRING;
    }
    normalized.data = new_normalized_data;

    return normalized;
    #undef APPEND
}
