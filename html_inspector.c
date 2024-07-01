#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <ctype.h>

static const char *ENTITIES[256] = {
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

static const char CHARMASK_WHITESPACE[256] = {
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
};

static const char CHARMASK_ATTRIBUTE_NAME_END[256] = {
    [ '='] = 1,
    ['\0'] = 1,
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
    [ '>'] = 1,
};

static const char CHARMASK_ATTRIBUTE_VALUE_END[256] = {
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
    [ '>'] = 1,
    ['\0'] = 1,
};

static const char CHARMASK_TAG_NAME_END[256] = {
    ['\0'] = 1,
    [ '"'] = 1,
    ['\''] = 1,
    [ ' '] = 1,
    ['\n'] = 1,
    ['\t'] = 1,
    ['\r'] = 1,
    [ '/'] = 1,
    [ '>'] = 1
};

struct String {
    unsigned char *data;
    size_t length;
    bool is_malloced;
};

#define STRING(cstring) (struct String) {cstring, sizeof cstring - 1, 0}
#define NULL_STRING (struct String) {NULL, 0, false}

void HtmlDocument_entities_to_utf8(struct String *input, bool skip_stray_tags)
{
    struct String result = (struct String) {malloc(input->length), 0, true};
    if (result.data == NULL) {
        if (input->is_malloced) {
            free(input->data);
        }
        *input = NULL_STRING;
        return;
    }

    int i, k;

    for (i = 0; i < input->length; ++i) {
        if (skip_stray_tags && input->data[i] == '<') { // Skipping stray tags
            do {
                i += 1;
            } while (i < input->length && input->data[i] != '>');
            continue;
        }
        if (input->data[i] != '&') {
            result.data[result.length] = input->data[i];
            result.length += 1;
            continue;
        }
        if (input->data[i + 1] == '#') {
            int codepoint = 0;
            if (input->data[i + 2] == 'x') {
                for (k = 3; input->data[i + k] != ';'; ++k) {
                    if (input->data[i + k] >= '0' && input->data[i + k] <= '9') {
                        codepoint = codepoint * 16 + (input->data[i + k] - '0');
                    }
                    else if (input->data[i + k] >= 'A' && input->data[i + k] <= 'F') {
                        codepoint = codepoint * 16 + (10 + input->data[i + k] - 'A');
                    }
                    else if (input->data[i + k] >= 'a' && input->data[i + k] <= 'f') {
                        codepoint = codepoint * 16 + (10 + input->data[i + k] - 'a');
                    }
                    else {
                        codepoint = -1;
                        break;
                    }
                }
            }
            else {
                for (k = 2; input->data[i + k] != ';'; ++k) {
                    if (input->data[i + k] >= '0' && input->data[i + k] <= '9') {
                        codepoint = codepoint * 10 + (input->data[i + k] - '0');
                    }
                    else {
                        codepoint = -1;
                        break;
                    }
                }
            }
            if (codepoint > 0x7FFFFFFF) {
                codepoint = -1;
            }
            if (codepoint == -1) {
                result.data[result.length++] = '&';
                continue;
            }
            i += k;

            // See `man utf-8`

            if (codepoint <= 0x7F) {
                result.data[result.length++] = codepoint;
            }
            else if (codepoint <= 0x7FF) {
                result.data[result.length++] = 0b11000000 + (codepoint >> 6);
                result.data[result.length++] = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0xFFFF) {
                result.data[result.length++] = 0b11100000 + (codepoint >> 12);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 6) & 0b111111);
                result.data[result.length++] = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x1FFFFF) {
                result.data[result.length++] = 0b11110000 + (codepoint >> 18);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 12) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 6) & 0b111111);
                result.data[result.length++] = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x03FFFFFF) {
                result.data[result.length++] = 0b11111000 + (codepoint >> 24);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 18) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 12) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 6) & 0b111111);
                result.data[result.length++] = (10 << 6) + (codepoint & 0b111111);
            }
            else if (codepoint <= 0x7FFFFFFF) {
                result.data[result.length++] = 0b1111110 + (codepoint >> 30);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 24) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 18) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 12) & 0b111111);
                result.data[result.length++] = (10 << 6) + ((codepoint >> 6) & 0b111111);
                result.data[result.length++] = (10 << 6) + (codepoint & 0b111111);
            }
            continue;
        }
        if (i + 1 == input->length || ENTITIES[input->data[i + 1]] == NULL) {
            result.data[result.length++] = '&';
            continue;
        }
        unsigned char entity[40] = {'&'};
        k = 1;
        do {
            if (k == sizeof entity - 1 || i + k == input->length) {
                break;
            }
            entity[k] = input->data[i + k];
        } while (entity[k++] != ';');
        if (entity[k - 1] != ';') {
            result.data[result.length++] = '&';
            continue;
        }
        entity[k] = '\0';
        const char *pos = strstr(ENTITIES[entity[1]], entity);
        if (pos == NULL) {
            result.data[result.length++] = '&';
            continue;
        }
        i += k - 1;
        if (pos[k] == '&') { // Special case for the &amp; entity
            result.data[result.length++] = '&';
        }
        while (pos[k] != '&' && pos[k] != '\0') {
            result.data[result.length++] = pos[k];
            k += 1;
        }
    }
    if (input->is_malloced) {
        free(input->data);
    }
    if (input->length != result.length) {
        char *realloced = realloc(result.data, result.length);
        if (realloced == NULL) {
            free(result.data);
            *input = NULL_STRING;
            return;
        }
        result.data = realloced;
    }
    *input = result;
}

void string_free(struct String string)
{
    if (string.is_malloced && string.data != NULL) {
        free(string.data);
    }
}

static int strnicmp(const char *s1, const char *s2, size_t length)
{
    int diff = 0;
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

struct HtmlDocument {
    const unsigned char *html;
    struct Node {
        union {
            const unsigned char *name_start;
            const unsigned char *value_start;
        };
        union {
            unsigned int name_length;
            unsigned int value_length;
        };
        unsigned int attributes_start;
        unsigned short nesting_level;
        unsigned short attributes_count;
        enum NodeType {
            NODE_TYPE_DOCUMENT,
            NODE_TYPE_COMMENT,
            NODE_TYPE_VOID_ELEMENT,
            NODE_TYPE_UNCLOSED_ELEMENT,
            NODE_TYPE_NONVOID_ELEMENT,
            NODE_TYPE_DOCTYPE,
            NODE_TYPE_TEXT,
            NODE_TYPE_CDATA,
        } type;
    } *nodes;
    struct Attribute {
        const unsigned char *name_start;
        const unsigned char *value_start;
        unsigned short name_length;
        unsigned short value_length;
    } *attributes;
    unsigned int node_count;
};

static const int POSITION_NOT_STARTED = -1;
static const int POSITION_EXHAUSTED = -2;
static const int POSITION_IS_FILTER = -3;

enum SelectorItemType {
    AXIS_CHILD,
    AXIS_ANCESTOR,
    AXIS_DESCENDANT,
    AXIS_FOLLOWING_SIBLING,
    AXIS_PRECEDING_SIBLING,
    FILTER_OR,
    FILTER_NOT,
    FILTER_AND,
    FILTER_CASE_I,
    FILTER_NTH,
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

struct Selector {
    struct HtmlDocument *doc;
    struct Node *reference_node;
    unsigned int active_axis;
    struct SelectorItem {
        union {
            struct {
                signed int position;
                unsigned int axis_n;
            };
            struct {
                const void *arg1;
                const void *arg2;
            } filter_data;
        };
        enum SelectorItemType type;
    } items[128];
    unsigned char item_count;
};

/*****************************************************************************/

static bool parse_attribute(struct Attribute *attribute, const unsigned char **html_ptr)
{
    const char *html = *html_ptr;
    while (CHARMASK_WHITESPACE[*html]) {
        html += 1;
    }
    if (*html == '>' || *html == '\0' || *html == '/' && html[1] == '>') {
        *html_ptr = html;
        return false;
    }
    attribute->name_start = html;
    attribute->name_length = 0;
    attribute->value_length = 0;
    do {
        attribute->name_length += 1;
        html += 1;
    } while (CHARMASK_ATTRIBUTE_NAME_END[*html] == 0);
    while (CHARMASK_WHITESPACE[*html]) {
        html += 1;
    }
    if (*html != '=') {
        attribute->value_start = html;
        *html_ptr = html;
        return true;
    }
    do {
        html += 1;
    } while (CHARMASK_WHITESPACE[*html]);
    if (*html == '"' || *html == '\'') {
        char quot = *html;
        html += 1;
        attribute->value_start = html;
        while (*html != '\0' && *html != quot) {
            attribute->value_length += 1;
            html += 1;
        }
        if (*html == quot) {
            html += 1;
        }
    }
    else {
        attribute->value_start = html;
        do {
            attribute->value_length += 1;
            html += 1;
        } while (CHARMASK_ATTRIBUTE_VALUE_END[*html] == 0);
    }
    while (CHARMASK_WHITESPACE[*html]) {
        html += 1;
    }
    *html_ptr = html;
    return true;
}

#define CHARSEQICMP(s1, length, s2) (length != sizeof s2 - 1 || strnicmp(s1, s2, length))

struct String HtmlDocument_extract_charset(const unsigned char *html)
{
    struct Attribute attribute;
    const unsigned char *html_start = html;
    while (true) {
        if (*html == '\0') {
            break;
        }
        if (!strncmp(html, "<!--", 4)) {
            html += 4;
            while (
                *html != '\0' &&
                (*html != '-' || html[1] != '-' || html[2] != '>')
            ) {
                html += 1;
            }
            if (html - html_start > 1024 || *html == '\0') {
                break;
            }
        }
        if (*html == '<') {
            html += 1;
            const char *name_start = html;
            int name_length = 0;
            while (CHARMASK_TAG_NAME_END[html[name_length]] == 0) {
                name_length += 1;
            }
            if (!CHARSEQICMP(name_start, name_length, "script") ||
                !CHARSEQICMP(name_start, name_length, "style") ||
                !CHARSEQICMP(name_start, name_length, "title") ||
                !CHARSEQICMP(name_start, name_length, "textarea"))
            {
                html += name_length;
                do {
                    html += 1;
                } while (
                    *html != '\0' && (*html != '<' || *(html + 1) != '/' ||
                    strnicmp(&html[2], name_start, name_length))
                );
            }
        }
        if (!strnicmp(html, "<meta", sizeof "<meta" - 1)) {
            html += 1;
            if (html - html_start > 1024) {
                break;
            }
            continue;
        }
        html += sizeof "<meta" - 1;
        bool has_http_equiv_content_type = false;
        struct String content = NULL_STRING;
        while (parse_attribute(&attribute, &html)) {
            if (!strnicmp(attribute.name_start, "charset", attribute.name_length)) {
                struct String result = {(char *) attribute.value_start, attribute.value_length, false};
                HtmlDocument_entities_to_utf8(&result, false);
                return result;
            }
            if (!strnicmp(attribute.name_start, "content", attribute.name_length)) {
                content.data = (char *) attribute.value_start;
                content.length = attribute.value_length;
            }
            else if (!strnicmp(attribute.name_start, "http-equiv", attribute.name_length)) {
                struct String attrval = {(char *) attribute.value_start, attribute.value_length, false};
                HtmlDocument_entities_to_utf8(&attrval, false);
                if (!strnicmp(attrval.data, "content-type", attrval.length)) {
                    has_http_equiv_content_type = true;
                }
                string_free(attrval);
            }
        }
        if (has_http_equiv_content_type && content.data != NULL) {
            HtmlDocument_entities_to_utf8(&content, false);
            int charset_begin = 0, charset_length = 0;
            for (; charset_begin < content.length; ++charset_begin) {
                if (content.data[charset_begin] != ';') {
                    continue;
                }
                do {
                    charset_begin += 1;
                } while (CHARMASK_WHITESPACE[content.data[charset_begin]]);
                if (strncmp(&content.data[charset_begin], "charset", sizeof "charset" - 1)) {
                    continue;
                }
                char charset_delim = content.data[charset_begin + sizeof "charset" - 1];
                if (charset_delim != '=' && !CHARMASK_WHITESPACE[charset_delim]) {
                    continue;
                }
                charset_begin += sizeof "charset" - 1;
                while (CHARMASK_WHITESPACE[content.data[charset_begin]]) {
                    charset_begin += 1;
                }
                if (content.data[charset_begin] != '=') {
                    continue;
                }
                do {
                    charset_begin += 1;
                } while (CHARMASK_WHITESPACE[content.data[charset_begin]]);
                if (content.data[charset_begin] == '"') {
                    // Quotes around charset are valid: https://www.ietf.org/rfc/rfc2045.txt
                    charset_begin += 1;
                }
                while (
                    charset_begin + charset_length < content.length &&
                    !CHARMASK_WHITESPACE[content.data[charset_begin + charset_length]] &&
                    content.data[charset_begin + charset_length] != ';'&&
                    content.data[charset_begin + charset_length] != '"'
                ) {
                    charset_length += 1;
                }
                break;
            }
            struct String result = {malloc(charset_length), charset_length, true};
            if (result.data == NULL) {
                string_free(content);
                return NULL_STRING;
            }
            memcpy(result.data, &content.data[charset_begin], charset_length);
            string_free(content);
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
    free(doc->nodes);
    free(doc);
}

static struct HtmlDocument * HtmlDocument(const unsigned char *html)
{
    // Minimizing the number of `realloc` calls is essential to achieve the best performance. We
    // use heuristic starting values depending on the input length. `strlen` is very fast.
    // `*_capacity` must be greater than zero to avoid invalid memory write operations.

    int html_strlen = strlen(html);
    int nodes_capacity = 100 + html_strlen / 40;
    int attributes_capacity = 100 + nodes_capacity * 2.4;

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
    int unclosed_elements_size = 0;
    int unclosed_elements_capacity = 100;
    int *unclosed_elements = malloc(unclosed_elements_capacity * sizeof *unclosed_elements);
    if (unclosed_elements == NULL) {
        free(doc->nodes);
        free(doc);
        return NULL;
    }
    #define INCREMENT_UNCLOSED_ELEMENTS_SIZE() \
        if (++unclosed_elements_size == unclosed_elements_capacity - 1) { \
            unclosed_elements_capacity += 100; \
            int *new_unclosed_elements = realloc(unclosed_elements, \
                unclosed_elements_capacity * sizeof *unclosed_elements); \
            if (new_unclosed_elements == NULL) { \
                free(unclosed_elements); \
                HtmlDocument_free(doc); \
                return NULL; \
            } \
            unclosed_elements = new_unclosed_elements; \
        }

    doc->nodes[0] = (struct Node) {
        .name_start = "#document",
        .name_length = sizeof "#document" - 1,
        .attributes_count = 0,
        .type = NODE_TYPE_DOCUMENT
    };
    doc->node_count = 1;
    doc->html = html;

    int attributes_count = 0;
    int html_node = -1, head_node = -1, body_node = -1, tbody_node = -2, colgroup_node = -1;

    // Optimized standard library functions such as strchr and strpbrk traverse the string word for
    // word and not byte for byte. But called in a loop, they are slower because of the overhead of
    // calculating the bitmasks in every call.

    #define INCREMENT_NODE_COUNT() \
        if (++doc->node_count == nodes_capacity - 1) { \
            nodes_capacity = 1 + (int) (nodes_capacity * 1.2); \
            struct Node *new_nodes = realloc(doc->nodes, nodes_capacity * sizeof *new_nodes); \
            if (new_nodes == NULL) { \
                free(unclosed_elements); \
                HtmlDocument_free(doc); \
                return NULL; \
            } \
            doc->nodes = new_nodes; \
        }

    while (true) {
        if (*html == '<') {
            html += 1;
            if (html[0] == '!' && html[1] == '-' && html[2] == '-') {
                html += 3;
                const unsigned char *comment_start = html;
                while (html[0] != '\0' && (html[0] != '-' || html[1] != '-' || html[2] != '>')) {
                    html += 1;
                }
                doc->nodes[doc->node_count] = (struct Node) {
                    .name_start = comment_start,
                    .name_length = html - comment_start,
                    .type = NODE_TYPE_COMMENT,
                    .nesting_level = 1,
                };
                INCREMENT_NODE_COUNT();
                if (*html != '\0') {
                    html += 3;
                }
            }
            else if (*html == '/') { // Closing tag
                html += 1;
                int name_length = 0;
                while (CHARMASK_TAG_NAME_END[html[name_length]] == 0) {
                    name_length += 1;
                }

                bool has_found_start_node = false;
                struct Node *node;
                int k;
                for (k = unclosed_elements_size - 1; k >= 0; --k) {
                    node = &doc->nodes[unclosed_elements[k]];
                    if (name_length == node->name_length && !strnicmp(node->name_start, html, name_length)) {
                        has_found_start_node = true;
                        break;
                    }
                }
                if (has_found_start_node) {
                    // Here we close all unclosed nodes between the matching start node and the last node.
                    // Example:
                    // <a>
                    // <b>  ← indent_width = 1
                    // text ← indent_width = 2
                    // <c>  ← indent_width = 2
                    // </a>
                    int indent_width = unclosed_elements_size - k;
                    for (int node_index = doc->node_count - 1; node_index >= unclosed_elements[k]; --node_index) {
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
                if (*html == '>') {
                    html += 1;  // Skipping over `>`
                }
                if (has_found_start_node || *html == '\0') {
                    continue;
                }

                // Not start tag found. We extend the current text node until the next `<`
                // following the stray tag. Stray tags are filtered out by the
                // `HtmlDocument_entities_to_utf8` function.

                node = &doc->nodes[doc->node_count - 1];
                if (node->type != NODE_TYPE_TEXT) {
                    continue;
                }
                while (*html != '<' && *html != '\0') {
                    html += 1;
                }
                node->value_length = html - node->value_start;
            }
            else {
                // Here we analyse a start tag. We use a loop to add nodes because we may need
                // to consider one or multiple optional start tags that are not encoded.

                const char *name = html;
                int name_length = 0;
                int new_attributes_count = attributes_count;

                while (CHARMASK_TAG_NAME_END[html[name_length]] == 0) {
                    name_length += 1;
                }
                html += name_length;
                while (parse_attribute(&doc->attributes[new_attributes_count], &html)) {
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
                if (*html == '/') {
                    html += 1;
                }
                html += 1;  // Skipping over `>`

                bool break_after_adding_node = false;
                do {
                    struct Node added_node, *node_for_attributes = NULL;

                    if (!CHARSEQICMP(name, name_length, "!DOCTYPE")) {
                        break;
                    }
                    else if (!CHARSEQICMP(name, name_length, "html")) {
                        if (html_node != -1) {
                            added_node.name_start = NULL;
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
                            added_node.name_start = NULL;
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
                            added_node.name_start = NULL;
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
                        node_for_attributes->attributes_start = attributes_count;
                        node_for_attributes->attributes_count = new_attributes_count - attributes_count;
                        attributes_count = new_attributes_count;
                    }
                    else {
                        added_node.attributes_count = 0;
                    }

                    if (added_node.name_start == NULL) {
                        break;
                    }

                    added_node.nesting_level = 1;
                    added_node.type = NODE_TYPE_UNCLOSED_ELEMENT;

                    // Using long if confitions is much faster than looping through data tables
                    // for the following tag-specific logic.

                    // Void elements
                    // https://html.spec.whatwg.org/multipage/syntax.html#void-elements

                    if (!CHARSEQICMP(added_node.name_start, added_node.name_length, "br") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "img") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "meta") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "link") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "input") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "embed") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "base") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "hr") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "col") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "area") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "wbr") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "source") ||
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "track"))
                    {
                        added_node.type = NODE_TYPE_VOID_ELEMENT;
                    }

                    // Auto-close unclosed nodes with optional end tag
                    // https://html.spec.whatwg.org/multipage/syntax.html#optional-tags

                    struct Node *node = &doc->nodes[unclosed_elements[unclosed_elements_size - 1]];

                    if (
                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "body") &&
                        !CHARSEQICMP(node->name_start, node->name_length, "head") ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "li") &&
                        !CHARSEQICMP(node->name_start, node->name_length, "li") ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "option") &&
                        !CHARSEQICMP(node->name_start, node->name_length, "option") ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "thead") &&
                        !CHARSEQICMP(node->name_start, node->name_length, "colgroup") ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "thead") &&
                        !CHARSEQICMP(node->name_start, node->name_length, "colgroup") ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "tbody") &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "colgroup") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "thead")
                        ) ||

                        !CHARSEQICMP(added_node.name_start, added_node.name_length, "tfoot") &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "colgroup") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "thead") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "tbody")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "td") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "th")
                        ) &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "td") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "th")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "dt") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "dd")
                        ) &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "dt") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "dd")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "rt") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "rp")
                        ) &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "rt") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "rp")
                        ) ||

                        (
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "optgroup") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "hr")
                        ) &&
                        (
                            !CHARSEQICMP(node->name_start, node->name_length, "optgroup") ||
                            !CHARSEQICMP(node->name_start, node->name_length, "option")
                        ) ||

                        !CHARSEQICMP(node->name_start, node->name_length, "p") &&
                        (
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "address") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "article") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "aside") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "blockquote") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "details") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "div") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "dl") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "fieldset") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "figcaption") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "figure") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "footer") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "form") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h1") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h2") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h3") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h4") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h5") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "h6") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "header") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "hgroup") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "hr") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "main") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "menu") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "nav") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "ol") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "p") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "pre") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "search") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "section") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "table") ||
                            !CHARSEQICMP(added_node.name_start, added_node.name_length, "ul")
                        )
                    ) {
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
        }
        if (*html == '\0') {
            break;
        }

        int text_node_length = 0;
        bool has_only_whitespace = true;
        enum NodeType type = NODE_TYPE_TEXT;

        struct Node *node = &doc->nodes[doc->node_count - 1];
        if (!CHARSEQICMP(node->name_start, node->name_length, "script") ||
            !CHARSEQICMP(node->name_start, node->name_length, "style") ||
            !CHARSEQICMP(node->name_start, node->name_length, "title") ||
            !CHARSEQICMP(node->name_start, node->name_length, "textarea"))
        {
            type = NODE_TYPE_CDATA;
            while (html[text_node_length] != '\0') {
                text_node_length += 1;
                if (html[text_node_length] == '<' && html[text_node_length + 1] == '/' &&
                    !strnicmp(&html[text_node_length + 2], node->name_start, node->name_length))
                {
                    break;
                }
            }
        }

        if (type == NODE_TYPE_TEXT) {
            while (html[text_node_length] != '<' && html[text_node_length] != '\0') {
                has_only_whitespace &= CHARMASK_WHITESPACE[html[text_node_length]];
                text_node_length += 1;
            }
        }

        if (text_node_length == 0) {
            continue;
        }

        if (type == NODE_TYPE_TEXT && !has_only_whitespace && body_node == -1) {
            if (html_node == -1) {
                doc->nodes[doc->node_count] = (struct Node) {
                    .name_start = "html",
                    .name_length = sizeof "html" - 1,
                    .type = NODE_TYPE_UNCLOSED_ELEMENT,
                    .nesting_level = 1,
                };
                html_node = doc->node_count;
                INCREMENT_NODE_COUNT();
            }
            doc->nodes[doc->node_count] = (struct Node) {
                .name_start = "body",
                .name_length = sizeof "body" - 1,
                .type = NODE_TYPE_UNCLOSED_ELEMENT,
                .nesting_level = 1,
            };
            body_node = doc->node_count;
            INCREMENT_NODE_COUNT();
            if (head_node != -1) {
                doc->nodes[head_node].type = NODE_TYPE_NONVOID_ELEMENT;
                for (int i = head_node + 1; i < doc->node_count - 1; ++i) {
                    doc->nodes[i].nesting_level += 1;
                }
                while (unclosed_elements[unclosed_elements_size - 1] != head_node) {
                    unclosed_elements_size -= 1;
                }
                unclosed_elements_size -= 1;
            }
            unclosed_elements[unclosed_elements_size] = body_node;
            INCREMENT_UNCLOSED_ELEMENTS_SIZE();
        }
        if (type == NODE_TYPE_CDATA || !has_only_whitespace || body_node != -1) {
            doc->nodes[doc->node_count] = (struct Node) {
                .type = type,
                .value_start = html,
                .value_length = text_node_length,
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

    // Next we realloc the data structures

    free(unclosed_elements);

    if (attributes_count == 0) {
        free(doc->attributes);
        doc->attributes = NULL;
    }
    else {
        struct Attribute *new_attributes = realloc(
            doc->attributes, attributes_count * sizeof *doc->attributes
        );
        if (new_attributes == NULL) {
            HtmlDocument_free(doc);
            return NULL;
        }
        doc->attributes = new_attributes;
    }

    struct Node *new_nodes = realloc(doc->nodes, doc->node_count * sizeof *doc->nodes);
    if (new_nodes == NULL) {
        HtmlDocument_free(doc);
        return NULL;
    }
    doc->nodes = new_nodes;

    return doc;
}

/*****************************************************************************/

static bool str_contains(const char *haystack, size_t haystack_length, const char *needle, bool is_word,
    bool case_i)
{
    int diff;
    for (int hi = 0, ni = 0; hi < haystack_length; ++hi) {
        if (is_word && hi > 0 && !CHARMASK_WHITESPACE[haystack[hi - 1]]) {
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
        if (needle[ni + 1] == '\0' && (!is_word || CHARMASK_WHITESPACE[haystack[hi + ni + 1]])) {
            return true;
        }
    }
    return false;
}

static void Selector_push_selector(struct Selector *sel, enum SelectorItemType type,
    const void *filter_arg1, const void *filter_arg2)
{
    if (sel->item_count == 0 && type >= FILTER_OR) {
        return;
    }
    if (sel->item_count == sizeof sel->items / sizeof *sel->items) {
        return;
    }
    sel->items[sel->item_count].type = type;
    if (type < FILTER_OR) {
        sel->items[sel->item_count].position = POSITION_NOT_STARTED;
        sel->items[sel->item_count].axis_n = 0;
    }
    else {
        sel->items[sel->item_count].filter_data.arg1 = filter_arg1;
        sel->items[sel->item_count].filter_data.arg2 = filter_arg2;
    }
    sel->item_count += 1;
}

void Selector_iterate_axis(struct Selector *sel, struct SelectorItem *si, const struct Node *ref)
{
    if (si->position == POSITION_NOT_STARTED) {
        si->position = ref - sel->doc->nodes;
    }

    if (si->type == AXIS_CHILD) {
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
        int current_nesting_level = sel->doc->nodes[si->position].nesting_level;
        while (--si->position >= 0) {
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
            const struct Node *node = &sel->doc->nodes[si->position--];
            if (node->nesting_level > ref->nesting_level) continue;
            if (node->nesting_level < ref->nesting_level) si->position = POSITION_EXHAUSTED;
            return;
        }
        si->position = POSITION_EXHAUSTED;
    }
    else if (si->type == AXIS_FOLLOWING_SIBLING) {
        while (si->position < sel->doc->node_count - 1) {
            const struct Node *node = &sel->doc->nodes[si->position++];
            if (node->nesting_level > ref->nesting_level) continue;
            if (node->nesting_level < ref->nesting_level) si->position = POSITION_EXHAUSTED;
            return;
        }
        si->position = POSITION_EXHAUSTED;
    }
}

static bool Selector_filter(struct Selector *sel, struct SelectorItem *si, struct Node *node)
{
    if (si->type == FILTER_NTH) {
        struct SelectorItem *axis_selector = si;
        while (true) {
            if (--axis_selector < sel->items) {
                return false;
            }
            if (axis_selector->type < FILTER_OR) {
                break;
            }
        }
        return axis_selector->axis_n == (long) si->filter_data.arg1;
    }
    else if (si->type == FILTER_NODE_NAME) {
        const char *name = (const char *) si->filter_data.arg1;
        const char *name_start;
        size_t name_length;
        if (node->type == NODE_TYPE_COMMENT) {
            name_start = "#comment";
            name_length = sizeof "#comment" - 1;
        }
        else if (node->type == NODE_TYPE_TEXT || node->type == NODE_TYPE_CDATA) {
            name_start = "#text";
            name_length = sizeof "#text" - 1;
        }
        else {
            name_start = node->name_start;
            name_length = node->name_length;
        }
        return name_length == strlen(name) && !strnicmp(name_start, name, name_length);
    }

    size_t name_length = strlen(si->filter_data.arg1);
    for (int i = 0; i < node->attributes_count; ++i) {
        struct Attribute *attr = &sel->doc->attributes[node->attributes_start + i];
        if (name_length != attr->name_length ||
            strnicmp(si->filter_data.arg1, attr->name_start, attr->name_length))
        {
            continue;
        }
        if (si->type == FILTER_ATTRIBUTE_EXISTS) {
            return true;
        }
        struct String attr_string = {(char *) attr->value_start, attr->value_length, false};
        HtmlDocument_entities_to_utf8(&attr_string, false);

        bool matches = false;
        if (si->type == FILTER_ATTRIBUTE_EQUALS) {
            matches = attr_string.length == strlen(si->filter_data.arg2) &&
                      !strncmp(si->filter_data.arg2, attr_string.data, attr_string.length);
        }
        else if (si->type == FILTER_ATTRIBUTE_EQUALS_I) {
            matches = attr_string.length == strlen(si->filter_data.arg2) &&
                      !strnicmp(si->filter_data.arg2, attr_string.data, attr_string.length);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS) {
            matches = str_contains(attr_string.data, attr_string.length, si->filter_data.arg2, false, false);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_I) {
            matches = str_contains(attr_string.data, attr_string.length, si->filter_data.arg2, false, true);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_WORD) {
            matches = str_contains(attr_string.data, attr_string.length, si->filter_data.arg2, true, false);
        }
        else if (si->type == FILTER_ATTRIBUTE_CONTAINS_WORD_I) {
            matches = str_contains(attr_string.data, attr_string.length, si->filter_data.arg2, true, true);
        }
        else if (si->type == FILTER_ATTRIBUTE_STARTS_WITH) {
            matches = !strncmp(si->filter_data.arg2, attr_string.data, strlen(si->filter_data.arg2));
        }
        else if (si->type == FILTER_ATTRIBUTE_STARTS_WITH_I) {
            matches = !strnicmp(si->filter_data.arg2, attr_string.data, strlen(si->filter_data.arg2));
        }
        string_free(attr_string);

        if (matches) {
            return true;
        }
    }
    return false;
}

int Selector_iterate(struct Selector *sel)
{
    // The logic here relies on the refusal to push filters to selector item position 0

    if (sel->item_count == 0 || sel->items[0].position == POSITION_EXHAUSTED) {
        return -1;
    }
    while (true) {
        int preceding_axis = sel->active_axis;
        while (--preceding_axis >= 0) {
            if (sel->items[preceding_axis].type < FILTER_OR) {
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
            } while (sel->active_axis > 0 && sel->items[sel->active_axis].type >= FILTER_OR);
            continue;
        }

        sel->items[sel->active_axis].axis_n += 1;

        unsigned int bool_stack_capacity = 0;
        int filter_index = sel->active_axis;
        while (++filter_index < sel->item_count &&
               sel->items[filter_index].type >= FILTER_OR)
        {
            bool_stack_capacity += 1;
        }
        bool bool_stack[bool_stack_capacity];
        filter_index = sel->active_axis;
        signed int bool_stack_size = 0;
        while (++filter_index < sel->item_count &&
               sel->items[filter_index].type >= FILTER_OR)
        {
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
        while (--bool_stack_size >= 0) {
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

        sel->active_axis = filter_index;
        sel->items[sel->active_axis].position = POSITION_NOT_STARTED;
        sel->items[sel->active_axis].axis_n = 0;
    }
}

void Selector_child(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_CHILD, NULL, NULL);
}

void Selector_ancestor(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_ANCESTOR, NULL, NULL);
}

void Selector_descendant(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_DESCENDANT, NULL, NULL);
}

void Selector_preceding_sibling(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_PRECEDING_SIBLING, NULL, NULL);
}

void Selector_following_sibling(struct Selector *sel)
{
    Selector_push_selector(sel, AXIS_FOLLOWING_SIBLING, NULL, NULL);
}

void Selector_nth(struct Selector *sel, unsigned int n)
{
    Selector_push_selector(sel, FILTER_NTH, (void *) (long) n, NULL);
}

void Selector_name(struct Selector *sel, const char *name)
{
    Selector_push_selector(sel, FILTER_NODE_NAME, name, NULL);
}

void Selector_attribute_exists(struct Selector *sel, const char *name)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_EXISTS, name, NULL);
}

void Selector_attribute_equals(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_EQUALS, name, value);
}

void Selector_attribute_contains(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_CONTAINS, name, value);
}

void Selector_attribute_starts_with(struct Selector *sel, const char *name, const char *value)
{
    Selector_push_selector(sel, FILTER_ATTRIBUTE_STARTS_WITH, name, value);
}

void Selector_or(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_OR, NULL, NULL);
}

void Selector_and(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_AND, NULL, NULL);
}

void Selector_not(struct Selector *sel)
{
    Selector_push_selector(sel, FILTER_NOT, NULL, NULL);
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

void HtmlDocument_reset(struct Selector *sel)
{
    sel->active_axis = 0;
    sel->item_count = 0;
}

struct String HtmlDocument_get_name(struct HtmlDocument *doc, int node)
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
    char *name = malloc(doc->nodes[node].name_length);
    if (name == NULL) {
        return NULL_STRING;
    }
    for (int i = 0; i < doc->nodes[node].name_length; ++i) {
        name[i] = tolower(doc->nodes[node].name_start[i]);
    }
    return (struct String) {name, doc->nodes[node].name_length, true};
}

struct String HtmlDocument_get_value(struct HtmlDocument *doc, int node)
{
    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    if (doc->nodes[node].type == NODE_TYPE_COMMENT || doc->nodes[node].type == NODE_TYPE_TEXT ||
        doc->nodes[node].type == NODE_TYPE_CDATA)
    {
        struct String value = {
            (unsigned char *) doc->nodes[node].value_start,
            doc->nodes[node].value_length,
            false
        };
        if (doc->nodes[node].type != NODE_TYPE_CDATA) {
            HtmlDocument_entities_to_utf8(&value, true);
        }
        return value;
    }
    return NULL_STRING;
}

struct String HtmlDocument_get_attribute(struct HtmlDocument *doc, int node, const char *attribute)
{
    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    int strlen_attribute = strlen(attribute);
    struct Attribute *attributes = &doc->attributes[doc->nodes[node].attributes_start];
    for (int i = 0; i < doc->nodes[node].attributes_count; ++i) {
        if (attributes[i].name_length == strlen_attribute &&
            !strnicmp(attributes[i].name_start, attribute, attributes[i].name_length))
        {
            struct String result = {(char *) attributes[i].value_start,attributes[i].value_length, false};
            HtmlDocument_entities_to_utf8(&result, false);
            return result;
        }
    }
    return NULL_STRING;
}

static int HtmlDocument_escape(struct String *html, bool attribute_mode)
{
    // https://dev.w3.org/html5/spec-LC/the-end.html#html-fragment-serialization-algorithm
    // Section: “Escaping a string”

    int result_length = html->length;
    for (int i = 0; i < html->length; ++i) {
        if (!attribute_mode && html->data[i] == '<') {
            result_length += sizeof "&lt;" - 2;
        }
        else if (!attribute_mode && html->data[i] == '>') {
            result_length += sizeof "&gt;" - 2;
        }
        else if (html->data[i] == '&') {
            result_length += sizeof "&amp;" - 2;
        }
        else if (attribute_mode && html->data[i] == '"') {
            result_length += sizeof "&quot;" - 2;
        }
        else if (html->data[i] == 0xC2 && i + 1 < html->length && html->data[i + 1] == 0xA0) {
            result_length += sizeof "&nbsp;" - 3;
            i += 1;
        }
    }
    if (result_length == html->length) {
        return 0;
    }
    struct String result = {malloc(result_length), 0, true};
    if (result.data == NULL) {
        return 1;
    }
    for (int i = 0; i < html->length; ++i) {
        if (!attribute_mode && html->data[i] == '<') {
            result.data[result.length++] = '&';
            result.data[result.length++] = 'l';
            result.data[result.length++] = 't';
            result.data[result.length++] = ';';
        }
        else if (!attribute_mode && html->data[i] == '>') {
            result.data[result.length++] = '&';
            result.data[result.length++] = 'g';
            result.data[result.length++] = 't';
            result.data[result.length++] = ';';
        }
        else if (html->data[i] == '&') {
            result.data[result.length++] = '&';
            result.data[result.length++] = 'a';
            result.data[result.length++] = 'm';
            result.data[result.length++] = 'p';
            result.data[result.length++] = ';';
        }
        else if (attribute_mode && html->data[i] == '"') {
            result.data[result.length++] = '&';
            result.data[result.length++] = 'q';
            result.data[result.length++] = 'u';
            result.data[result.length++] = 'o';
            result.data[result.length++] = 't';
            result.data[result.length++] = ';';
        }
        else if (html->data[i] == 0xC2 && i + 1 < html->length && html->data[i + 1] == 0xA0) {
            result.data[result.length++] = '&';
            result.data[result.length++] = 'n';
            result.data[result.length++] = 'b';
            result.data[result.length++] = 's';
            result.data[result.length++] = 'p';
            result.data[result.length++] = ';';
            i += 1;
        }
        else {
            result.data[result.length++] = html->data[i];
        }
    }
    if (html->is_malloced) {
        free(html->data);
    }
    *html = result;
    return 0;
}

static struct String HtmlDocument_get_html(struct HtmlDocument *doc, int node, bool inner)
{
    // https://dev.w3.org/html5/spec-LC/the-end.html#html-fragment-serialization-algorithm

    if (node < 0 || node >= doc->node_count) {
        return NULL_STRING;
    }
    size_t result_capacity = 1;
    struct String result = {malloc(result_capacity), 0, true};
    #define APPEND(_data, _length) \
        if (result.length + _length >= result_capacity) { \
            result_capacity += _length + 1024; \
            char *r = realloc(result.data, result_capacity); \
            if (r == NULL) { \
                free(result.data); \
                return NULL_STRING; \
            } \
            result.data = r; \
        } \
        memcpy(&result.data[result.length], _data, _length); \
        result.length += _length;

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
            APPEND("<!--", 4);
            APPEND(n->value_start, n->value_length);
            APPEND("-->", 3);
        }
        else if (n->type == NODE_TYPE_TEXT || n->type == NODE_TYPE_CDATA) {
            struct String value = {(char *) n->value_start, n->value_length, false};
            if (n->type != NODE_TYPE_CDATA) {
                HtmlDocument_entities_to_utf8(&value, true); // TODO check malloc failure
                HtmlDocument_escape(&value, false);
            }
            APPEND(value.data, value.length)
            string_free(value);
        }
        else {
            APPEND("<", 1);
            APPEND(n->name_start, n->name_length);

            // Spec.: “For HTML elements created by the HTML parser […], tagname will be lowercase.”

            for (int i = n->name_length + 1; i >= 1; --i) {
                result.data[result.length - i] = tolower(result.data[result.length - i]);
            }

            struct Attribute *attribute = &doc->attributes[n->attributes_start];
            while (attribute < &doc->attributes[n->attributes_start + n->attributes_count]) {
                APPEND(" ", 1);
                APPEND(attribute->name_start, attribute->name_length);

                // Spec.: “For attributes on HTML elements set by the HTML parser […], the
                // local name will be lowercase.”

                for (int i = attribute->name_length + 1; i >= 1; --i) {
                    result.data[result.length - i] = tolower(result.data[result.length - i]);
                }

                APPEND("=\"", 2)

                struct String value = {(char *) attribute->value_start, attribute->value_length, false};
                HtmlDocument_entities_to_utf8(&value, false); // TODO check malloc failure
                HtmlDocument_escape(&value, true);
                APPEND(value.data, value.length)
                string_free(value);

                APPEND("\"", 1)
                attribute += 1;

            }
            APPEND(">", 1)
        }
        int preceding_nesting_level = n->nesting_level;
        int next_nesting_level = n == last_node ||
            (n + 1)->nesting_level <= doc->nodes[node].nesting_level - 1 ?
            doc->nodes[node].nesting_level : (n + 1)->nesting_level;
        if (next_nesting_level <= preceding_nesting_level) {
            struct Node *counterpart = n;
            do {
                if (counterpart->nesting_level == preceding_nesting_level - 1 ||
                    counterpart->nesting_level == preceding_nesting_level &&
                    n->type == NODE_TYPE_NONVOID_ELEMENT)
                {
                    APPEND("</", 2);
                    APPEND(counterpart->name_start, counterpart->name_length);
                    for (int i = counterpart->name_length + 1; i >= 1; --i) {
                        result.data[result.length - i] = tolower(result.data[result.length - i]);
                    }
                    APPEND(">", 1);
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
    #undef APPEND
}

struct String HtmlDocument_get_inner_html(struct HtmlDocument *doc, int node)
{
    return HtmlDocument_get_html(doc, node, true);
}

struct String HtmlDocument_get_outer_html(struct HtmlDocument *doc, int node)
{
    return HtmlDocument_get_html(doc, node, false);
}

struct Selector * HtmlDocument_select(struct HtmlDocument *doc, unsigned int index)
{
    struct Selector *s = malloc(sizeof (struct Selector));
    if (s == NULL) {
        return NULL;
    }
    s->doc = doc;
    s->item_count = 0;
    s->active_axis = 0;
    s->reference_node = index < doc->node_count ? doc->nodes + index : doc->nodes;
    return s;
}

/*****************************************************************************/

static int from_hex(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c >= 'A' && c <= 'Z') return c - 'A';
    return -1;
}

struct String resolve_iri(struct String reference, struct String base)
{
    // Resolve UTF-8 encoded IRI references and convert to ASCII-encoded URI format.
    // The standard defines IRI resolving as the mapping to a URI followed by resolving the URI.
    //
    // Both input parameters are expected to have UTF-8 encoding.
    //
    // IRI: https://datatracker.ietf.org/doc/html/rfc3987
    // URI resolving: https://www.rfc-editor.org/rfc/rfc1808#section-5
    //
    // https://en.wikipedia.org/wiki/URI_normalization
    // https://www.rfc-editor.org/rfc/rfc3986#section-5.2.4
    //
    // TODO: We will convert IDNA to ASCII because some network clients may not support IDN, notably
    // PHP's `file_get_contents`. In cURL, IDN support is controlled via a build option.

    int i;
    enum {
        COMPONENT_SCHEME,
        COMPONENT_AUTHORITY,
        COMPONENT_ABSOLUTE_PATH,
        COMPONENT_RELATIVE_PATH,
        COMPONENT_QUERY_STRING,
        COMPONENT_FRAGMENT
    } reference_start_component;

    if (reference.length >= 2 && reference.data[0] == '/' && reference.data[1] == '/') {
        reference_start_component = COMPONENT_AUTHORITY;
    }
    else if (reference.length == 0 || reference.data[0] == '#') {
        reference_start_component = COMPONENT_FRAGMENT;
    }
    else if (reference.data[0] == '/') {
        reference_start_component = COMPONENT_ABSOLUTE_PATH;
    }
    else if (reference.data[0] == '?') {
        reference_start_component = COMPONENT_QUERY_STRING;
    }
    else {
        reference_start_component = COMPONENT_RELATIVE_PATH;
        for (i = 0; i < reference.length; ++i) {
            if (reference.data[i] == '?') {
                break;
            }
            if (reference.data[i] == ':') {
                reference_start_component = COMPONENT_SCHEME;
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

    struct String source = reference_start_component == COMPONENT_SCHEME ? reference : base;
    i = 0;

    // Copy the scheme from `source` to the result

    int scheme_length = 0;
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

    if (reference_start_component == COMPONENT_AUTHORITY) {
        source = reference;
        i = 0;
    }
    if (i + 1 < source.length && source.data[i] == '/' && source.data[i + 1] == '/') {
        int authority_start_index = i;
        int at_index = -1;
        for (i = authority_start_index + 2; i < source.length && source.data[i] != '/' &&
                source.data[i] != '?' && source.data[i] != '#' && source.data[i] != ':'; ++i)
        {
            if (source.data[i] == '@') {
                at_index = i;
            }
        }
        int domain_end_index = i;
        int domain_start_index = at_index >= 0 ? at_index + 1 : authority_start_index + 2;
        for (i = authority_start_index; i < domain_start_index; ++i) {
            APPEND(source.data[i]);
        }
        for (i = domain_start_index; i < domain_end_index; ++i) {
            if (source.data[i] > 127) {
                free(normalized.data);
                return NULL_STRING;
            }
            APPEND(tolower(source.data[i]));
        }
        if (source.data[i] == ':') {
            do {
                i += 1;
            } while (source.data[i] == '0');
            int port_start_i = i;
            int port = 0;
            while (
                i < source.length && source.data[i] != '/' && source.data[i] != '?' &&
                source.data[i] != '#'
            ) {
                char digit = source.data[i] - '0';
                if (digit < 0 || digit > 9) {
                    free(source.data);
                    return NULL_STRING;
                }
                port = 10 * port + digit;
                i += 1;
            }
            if ((port != 80 || strncmp(normalized.data, "http", scheme_length)) &&
                (port != 443 || strncmp(normalized.data, "https", scheme_length)))
            {
                APPEND(':');
                for (int k = port_start_i; k < i; ++k) {
                    APPEND(source.data[k]);
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

    if (reference_start_component == COMPONENT_ABSOLUTE_PATH) {
        source = reference;
        i = 1;
    }
    int cut_off;
    if (reference_start_component == COMPONENT_RELATIVE_PATH) {
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
    int normalized_path_start = normalized.length - 1;
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
            if (reference_start_component == COMPONENT_QUERY_STRING && source.data == base.data) {
                source = reference;
                i = 0;
            }
            APPEND('?');
        }
        else if (source.data[i] == '#') {
            is_in_path = false;
            if (reference_start_component == COMPONENT_FRAGMENT && source.data == base.data) {
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
            if (i + 2 > source.length - 1) {
                // Invalid URL
                APPEND('%');
                continue;
            }
            i += 1;
            char hex_digit1 = from_hex(source.data[i]);
            if (hex_digit1 < 0) {
                continue;
            }
            char hex_digit2 = from_hex(source.data[i + 1]);
            if (hex_digit2 < 0) {
                continue;
            }
            int hex = hex_digit1 * 16 + hex_digit2;
            if (hex >= 'a' && hex <= 'z' || hex >= 'A' && hex <= 'Z' ||
                hex == '-' || hex == '_' || hex == '.' || hex == '~')
            {
                APPEND(hex);
            }
            else {
                APPEND('%');
                APPEND(toupper(source.data[i]));
                APPEND(toupper(source.data[i + 1]));
            }
            i += 1;
        }
        else if (source.data[i] > 127) {
            APPEND('%');
            unsigned char x;
            x = source.data[i] >> 4;
            x += x < 10 ? '0' : 'A' - 10;
            APPEND(x);
            x = source.data[i] & 0b1111;
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
