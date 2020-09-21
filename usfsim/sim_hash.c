/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -k '*' -t -E -N simulator_struct_info -H ihash  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif


#include "hash.h"
#include "simulator.h"
#include "stddef.h"
#include "string.h"
struct StructInfo;
/* maximum key range = 465, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
ihash (register const char *str, register size_t len)
{
  static unsigned short asso_values[] =
    {
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473,   0, 473,  65, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473,   0,   0,  30,  35,  30,
       60,  75,   0,   5, 473,   0,   0,  60,  45, 473,
        0,   0,  60,  10,  60, 473, 125,   0, 473,   0,
      473, 473, 473, 473, 473,   0, 473,   0,   0,   0,
      115,   5,  35,   0,  20,   0, 473,   0,   0,   5,
        0,   0,   5,  45,  10,   0,   0,   0,  85, 110,
       10,  70,  40, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473, 473, 473, 473, 473,
      473, 473, 473, 473, 473, 473
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[32]];
      /*FALLTHROUGH*/
      case 32:
        hval += asso_values[(unsigned char)str[31]];
      /*FALLTHROUGH*/
      case 31:
        hval += asso_values[(unsigned char)str[30]];
      /*FALLTHROUGH*/
      case 30:
        hval += asso_values[(unsigned char)str[29]];
      /*FALLTHROUGH*/
      case 29:
        hval += asso_values[(unsigned char)str[28]];
      /*FALLTHROUGH*/
      case 28:
        hval += asso_values[(unsigned char)str[27]];
      /*FALLTHROUGH*/
      case 27:
        hval += asso_values[(unsigned char)str[26]];
      /*FALLTHROUGH*/
      case 26:
        hval += asso_values[(unsigned char)str[25]];
      /*FALLTHROUGH*/
      case 25:
        hval += asso_values[(unsigned char)str[24]];
      /*FALLTHROUGH*/
      case 24:
        hval += asso_values[(unsigned char)str[23]];
      /*FALLTHROUGH*/
      case 23:
        hval += asso_values[(unsigned char)str[22]];
      /*FALLTHROUGH*/
      case 22:
        hval += asso_values[(unsigned char)str[21]];
      /*FALLTHROUGH*/
      case 21:
        hval += asso_values[(unsigned char)str[20]];
      /*FALLTHROUGH*/
      case 20:
        hval += asso_values[(unsigned char)str[19]];
      /*FALLTHROUGH*/
      case 19:
        hval += asso_values[(unsigned char)str[18]];
      /*FALLTHROUGH*/
      case 18:
        hval += asso_values[(unsigned char)str[17]];
      /*FALLTHROUGH*/
      case 17:
        hval += asso_values[(unsigned char)str[16]];
      /*FALLTHROUGH*/
      case 16:
        hval += asso_values[(unsigned char)str[15]];
      /*FALLTHROUGH*/
      case 15:
        hval += asso_values[(unsigned char)str[14]];
      /*FALLTHROUGH*/
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      /*FALLTHROUGH*/
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

struct StructInfo *
simulator_struct_info (register const char *str, register size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 160,
      MIN_WORD_LENGTH = 5,
      MAX_WORD_LENGTH = 33,
      MIN_HASH_VALUE = 8,
      MAX_HASH_VALUE = 472
    };

  static struct StructInfo wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"Plot.lbl", offsetof (Plot,lbl), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""}, {""}, {""}, {""},
      {"Plot.cell", offsetof (Plot,cell), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"Plot.pop", offsetof (Plot,pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Plot.spike", offsetof (Plot,spike), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"Slice.ap", offsetof (Slice,ap), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"Slice.rl", offsetof (Slice,rl), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"simulator_global.net", offsetof (simulator_global,net), 0, 0, "Network", 0, sizeof (Network), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.plot", offsetof (simulator_global,plot), 0, 0, "Plot", 0, sizeof (Plot), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"simulator_global.slice", offsetof (simulator_global,slice), 0, 0, "Slice", 0, sizeof (Slice), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {"Slice.stepnum", offsetof (Slice,stepnum), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.nonoise", offsetof (simulator_global,nonoise), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"simulator_global.step", offsetof (simulator_global,step), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.plot_count", offsetof (simulator_global,plot_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.slice_count", offsetof (simulator_global,slice_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.B", offsetof (CellPop,B), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.nanlgpop", offsetof (simulator_global,nanlgpop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.x", offsetof (Cell,x), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.step_count", offsetof (simulator_global,step_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.gnoise_i", offsetof (Cell,gnoise_i), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"simulator_global.stepnum", offsetof (simulator_global,stepnum), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"Cell.spike", offsetof (Cell,spike), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"simulator_global.nanlgrate", offsetof (simulator_global,nanlgrate), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.cell", offsetof (CellPop,cell), 0, 0, "Cell", 0, sizeof (Cell), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.gnoise_e", offsetof (Cell,gnoise_e), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {""}, {""},
      {"Cell.target", offsetof (Cell,target), 0, 0, "Target", 0, sizeof (Target), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"CellPop.name", offsetof (CellPop,name), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.cell_count", offsetof (CellPop,cell_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.Ek", offsetof (simulator_global,Ek), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.sigma_m", offsetof (CellPop,sigma_m), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Cell.target_count", offsetof (Cell,target_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"CellPop.noise_amp", offsetof (CellPop,noise_amp), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.sclfct", offsetof (simulator_global,sclfct), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"CellPop.orig_cell_count", offsetof (CellPop,orig_cell_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.sigma_h", offsetof (CellPop,sigma_h), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.z", offsetof (Cell,z), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.targetpop", offsetof (CellPop,targetpop), 0, 0, "TargetPop", 0, sizeof (TargetPop), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"CellPop.theta_m", offsetof (CellPop,theta_m), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.taubar_h", offsetof (CellPop,taubar_h), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Fiber.signal", offsetof (Fiber,signal), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.targetpop_count", offsetof (CellPop,targetpop_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Plot.type", offsetof (Plot,type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Fiber.state", offsetof (Fiber,state), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.lmmfr", offsetof (simulator_global,lmmfr), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Plot.val", offsetof (Plot,val), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.fr", offsetof (CellPop,fr), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.ic_expression", offsetof (CellPop,ic_expression), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {"Syn.lrn", offsetof (Syn,lrn), 0, 0, "LEARN", 0, sizeof (LEARN), 1, 1, 0, 0, 1, 0, 0, 0, 1},
      {"FiberPop.stop", offsetof (FiberPop,stop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.theta_h", offsetof (CellPop,theta_h), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.input_filename", offsetof (simulator_global,input_filename), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {"Fiber.target", offsetof (Fiber,target), 0, 0, "Target", 0, sizeof (Target), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {"Plot.var", offsetof (Plot,var), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.start", offsetof (FiberPop,start), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"Fiber.target_count", offsetof (Fiber,target_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"Cell.y", offsetof (Cell,y), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.lumbar_equation", offsetof (simulator_global,lumbar_equation), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"Cell.syn", offsetof (Cell,syn), 0, 0, "Syn", 0, sizeof (Syn), 1, 1, 1, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"Syn.EQ", offsetof (Syn,EQ), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.Gk", offsetof (Cell,Gk), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"FiberPop.next_stim", offsetof (FiberPop,next_stim), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 1, 0, 0},
      {"Cell.syn_count", offsetof (Cell,syn_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.g_NaP_h", offsetof (CellPop,g_NaP_h), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"FiberPop.targetpop", offsetof (FiberPop,targetpop), 0, 0, "TargetPop", 0, sizeof (TargetPop), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Target.strength", offsetof (Target,strength), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"Cell.sub_type", offsetof (Cell,sub_type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.targetpop_count", offsetof (FiberPop,targetpop_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.q", offsetof (Syn,q), ato_float_star, str_float_star, 0, 0, sizeof (float), 1, 1, 0, 0, 0, 1, 0, 0, 0},
      {""}, {""},
      {"Cell.Thr", offsetof (Cell,Thr), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {""},
      {"Syn.initial_strength", offsetof (Syn,initial_strength), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.q_count", offsetof (Syn,q_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"Slice.d", offsetof (Slice,d), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.phrenic_equation", offsetof (simulator_global,phrenic_equation), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {""},
      {"simulator_global.ispresynaptic", offsetof (simulator_global,ispresynaptic), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.lrn_strength", offsetof (Syn,lrn_strength), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Slice.dp", offsetof (Slice,dp), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.fiber", offsetof (FiberPop,fiber), 0, 0, "Fiber", 0, sizeof (Fiber), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"simulator_global.save_smr", offsetof (simulator_global,save_smr), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.save_pop_total", offsetof (simulator_global,save_pop_total), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.lrn_size", offsetof (Syn,lrn_size), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.pop_subtype", offsetof (CellPop,pop_subtype), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.fiber_count", offsetof (FiberPop,fiber_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"simulator_global.dcgint", offsetof (simulator_global,dcgint), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.nanlgid", offsetof (simulator_global,nanlgid), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Target.syn", offsetof (Target,syn), 0, 0, "Syn", 0, sizeof (Syn), 1, 1, 0, 0, 1, 0, 0, 0, 1},
      {""},
      {"simulator_global.cwrit", offsetof (simulator_global,cwrit), 0, 0, "Plot", 0, sizeof (Plot), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"simulator_global.save_spike_times", offsetof (simulator_global,save_spike_times), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.outsned", offsetof (simulator_global,outsned), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.G", offsetof (Syn,G), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"simulator_global.seed", offsetof (simulator_global,seed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {"Syn.DCS", offsetof (Syn,DCS), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.cwrit_count", offsetof (simulator_global,cwrit_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"Syn.lrnStrDelta", offsetof (Syn,lrnStrDelta), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"FiberPop.offset", offsetof (FiberPop,offset), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.num_aff", offsetof (FiberPop,num_aff), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Cell.Vm", offsetof (Cell,Vm), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {""}, {""},
      {"CellPop.R0", offsetof (CellPop,R0), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.DCTH", offsetof (CellPop,DCTH), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"simulator_global.spawn_number", offsetof (simulator_global,spawn_number), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.Gm0", offsetof (simulator_global,Gm0), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"FiberPop.aff_prob", offsetof (FiberPop,aff_prob), ato_double, str_double, 0, 0, sizeof (double), 32, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.synparent", offsetof (Syn,synparent), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"TargetPop.TYPE", offsetof (TargetPop,TYPE), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.probability", offsetof (FiberPop,probability), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.TGK", offsetof (CellPop,TGK), ato_double, str_double, 0, 0, sizeof (double), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.file_subversion", offsetof (simulator_global,file_subversion), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.noise_seed", offsetof (CellPop,noise_seed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 1},
      {"TargetPop.IRCP", offsetof (TargetPop,IRCP), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.pop_subtype", offsetof (FiberPop,pop_subtype), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.DCG", offsetof (CellPop,DCG), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.fwrit", offsetof (simulator_global,fwrit), 0, 0, "Plot", 0, sizeof (Plot), 1, 1, 0, 0, 0, 0, 1, 0, 0},
      {"Syn.lrnStrMax", offsetof (Syn,lrnStrMax), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.delta_h", offsetof (CellPop,delta_h), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.Th0", offsetof (CellPop,Th0), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"TargetPop.NT", offsetof (TargetPop,NT), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"simulator_global.fwrit_count", offsetof (simulator_global,fwrit_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.Vreset", offsetof (CellPop,Vreset), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Network.cellpop", offsetof (Network,cellpop), 0, 0, "CellPop", 0, sizeof (CellPop), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""},
      {"Network.cellpop_count", offsetof (Network,cellpop_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"simulator_global.snd_file_name", offsetof (simulator_global,snd_file_name), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""},
      {"Syn.cidx", offsetof (Syn,cidx), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Syn.stidx", offsetof (Syn,stidx), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.MGC", offsetof (CellPop,MGC), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"Syn.cpidx", offsetof (Syn,cpidx), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"TargetPop.INSED", offsetof (TargetPop,INSED), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"CellPop.GE0", offsetof (CellPop,GE0), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"TargetPop.STR", offsetof (TargetPop,STR), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"TargetPop.NCT", offsetof (TargetPop,NCT), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"simulator_global.Vm0", offsetof (simulator_global,Vm0), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"CellPop.Vthresh", offsetof (CellPop,Vthresh), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""},
      {"Syn.syntype", offsetof (Syn,syntype), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"TargetPop.MCT", offsetof (TargetPop,MCT), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"Network.fiberpop", offsetof (Network,fiberpop), 0, 0, "FiberPop", 0, sizeof (FiberPop), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.afferent_file_name", offsetof (FiberPop,afferent_file_name), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""},
      {"FiberPop.infsed", offsetof (FiberPop,infsed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 1, 0, 0, 1},
      {"FiberPop.aff_val", offsetof (FiberPop,aff_val), ato_double, str_double, 0, 0, sizeof (double), 32, 0, 0, 0, 0, 0, 0, 0, 1},
      {"Network.fiberpop_count", offsetof (Network,fiberpop_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"LEARN.ariv_time", offsetof (LEARN,ariv_time), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"LEARN.recv_pop", offsetof (LEARN,recv_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"SynType.EQ", offsetof (SynType,EQ), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"CellPop.TMEM", offsetof (CellPop,TMEM), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""},
      {"FiberPop.frequency", offsetof (FiberPop,frequency), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"LEARN.recv_term", offsetof (LEARN,recv_term), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"simulator_global.update_interval", offsetof (simulator_global,update_interval), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"FiberPop.freq_type", offsetof (FiberPop,freq_type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"Target.delay", offsetof (Target,delay), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"FiberPop.next_fixed", offsetof (FiberPop,next_fixed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 1, 0, 0},
      {""}, {""},
      {"Cell.Vm_prev", offsetof (Cell,Vm_prev), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 1, 0, 0, 0},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"LEARN.send_term", offsetof (LEARN,send_term), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"FiberPop.fuzzy_range", offsetof (FiberPop,fuzzy_range), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""},
      {"SynType.DCS", offsetof (SynType,DCS), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"SynType.lrnStrDelta", offsetof (SynType,lrnStrDelta), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"CellPop.Th0_sd", offsetof (CellPop,Th0_sd), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""},
      {"Syn.lrnWindow", offsetof (Syn,lrnWindow), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"Network.syntype", offsetof (Network,syntype), 0, 0, "SynType", 0, sizeof (SynType), 1, 1, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"SynType.lrnStrMax", offsetof (SynType,lrnStrMax), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"Network.syntype_count", offsetof (Network,syntype_count), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"simulator_global.save_smr_wave", offsetof (simulator_global,save_smr_wave), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
      {"SynType.SYN_TYPE", offsetof (SynType,SYN_TYPE), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
      {"SynType.PARENT", offsetof (SynType,PARENT), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"SynType.lrnWindow", offsetof (SynType,lrnWindow), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = ihash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}

/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -k '*' -t -E -N simulator_struct_members -H mhash  */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
#error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gperf@gnu.org>."
#endif


char *members_Slice[] = {
    "stepnum",
    "ap",
    "rl",
    "dp",
    "d",
    0
};
char *members_LEARN[] = {
    "recv_pop",
    "send_term",
    "recv_term",
    "ariv_time",
    0
};
char *members_Syn[] = {
    "G",
    "EQ",
    "DCS",
    "q_count",
    "q",
    "cpidx",
    "cidx",
    "stidx",
    "syntype",
    "synparent",
    "initial_strength",
    "lrn_strength",
    "lrnWindow",
    "lrnStrMax",
    "lrnStrDelta",
    "lrn_size",
    "lrn",
    0
};
char *members_Target[] = {
    "delay",
    "strength",
    "syn",
    0
};
char *members_Cell[] = {
    "Vm_prev",
    "Vm",
    "Gk",
    "Thr",
    "gnoise_e",
    "gnoise_i",
    "spike",
    "syn_count",
    "syn",
    "target_count",
    "target",
    "x",
    "y",
    "z",
    "sub_type",
    0
};
char *members_Fiber[] = {
    "state",
    "signal",
    "target_count",
    "target",
    0
};
char *members_TargetPop[] = {
    "MCT",
    "NCT",
    "NT",
    "IRCP",
    "INSED",
    "TYPE",
    "STR",
    0
};
char *members_FiberPop[] = {
    "start",
    "stop",
    "infsed",
    "probability",
    "fiber_count",
    "fiber",
    "targetpop_count",
    "targetpop",
    "pop_subtype",
    "freq_type",
    "frequency",
    "fuzzy_range",
    "next_stim",
    "next_fixed",
    "afferent_file_name",
    "num_aff",
    "offset",
    "aff_val",
    "aff_prob",
    0
};
char *members_CellPop[] = {
    "R0",
    "TMEM",
    "B",
    "DCG",
    "GE0",
    "MGC",
    "DCTH",
    "Th0",
    "Th0_sd",
    "theta_h",
    "sigma_h",
    "theta_m",
    "sigma_m",
    "Vreset",
    "Vthresh",
    "delta_h",
    "taubar_h",
    "g_NaP_h",
    "orig_cell_count",
    "cell_count",
    "cell",
    "targetpop_count",
    "targetpop",
    "noise_amp",
    "noise_seed",
    "fr",
    "TGK",
    "name",
    "ic_expression",
    "pop_subtype",
    0
};
char *members_SynType[] = {
    "EQ",
    "DCS",
    "lrnWindow",
    "lrnStrMax",
    "lrnStrDelta",
    "SYN_TYPE",
    "PARENT",
    0
};
char *members_Plot[] = {
    "pop",
    "cell",
    "var",
    "type",
    "lbl",
    "val",
    "spike",
    0
};
char *members_Network[] = {
    "fiberpop_count",
    "fiberpop",
    "cellpop_count",
    "cellpop",
    "syntype_count",
    "syntype",
    0
};
char *members_simulator_global[] = {
    "file_subversion",
    "slice_count",
    "slice",
    "net",
    "step_count",
    "step",
    "Gm0",
    "Vm0",
    "Ek",
    "snd_file_name",
    "input_filename",
    "update_interval",
    "outsned",
    "save_spike_times",
    "save_smr",
    "save_smr_wave",
    "save_pop_total",
    "spawn_number",
    "plot_count",
    "plot",
    "fwrit_count",
    "fwrit",
    "cwrit_count",
    "cwrit",
    "nanlgid",
    "nanlgpop",
    "nanlgrate",
    "sclfct",
    "dcgint",
    "stepnum",
    "ispresynaptic",
    "nonoise",
    "seed",
    "phrenic_equation",
    "lumbar_equation",
    "lmmfr",
    0
};
struct StructMembers;
/* maximum key range = 15, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
mhash (register const char *str, register size_t len)
{
  static unsigned char asso_values[] =
    {
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18,  5, 18, 10, 18,  0,
       0, 18, 18, 18, 18, 18,  0, 18,  5, 18,
       0, 18,  0,  0,  0, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18,  0, 18,  0,  0,  5,
      18,  0, 18,  0, 18,  0, 18,  0,  0,  0,
       0,  0,  0, 18,  0,  0,  0,  0, 18,  0,
      18,  0, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18, 18, 18, 18, 18,
      18, 18, 18, 18, 18, 18
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[15]];
      /*FALLTHROUGH*/
      case 15:
        hval += asso_values[(unsigned char)str[14]];
      /*FALLTHROUGH*/
      case 14:
        hval += asso_values[(unsigned char)str[13]];
      /*FALLTHROUGH*/
      case 13:
        hval += asso_values[(unsigned char)str[12]];
      /*FALLTHROUGH*/
      case 12:
        hval += asso_values[(unsigned char)str[11]];
      /*FALLTHROUGH*/
      case 11:
        hval += asso_values[(unsigned char)str[10]];
      /*FALLTHROUGH*/
      case 10:
        hval += asso_values[(unsigned char)str[9]];
      /*FALLTHROUGH*/
      case 9:
        hval += asso_values[(unsigned char)str[8]];
      /*FALLTHROUGH*/
      case 8:
        hval += asso_values[(unsigned char)str[7]];
      /*FALLTHROUGH*/
      case 7:
        hval += asso_values[(unsigned char)str[6]];
      /*FALLTHROUGH*/
      case 6:
        hval += asso_values[(unsigned char)str[5]];
      /*FALLTHROUGH*/
      case 5:
        hval += asso_values[(unsigned char)str[4]];
      /*FALLTHROUGH*/
      case 4:
        hval += asso_values[(unsigned char)str[3]];
      /*FALLTHROUGH*/
      case 3:
        hval += asso_values[(unsigned char)str[2]];
      /*FALLTHROUGH*/
      case 2:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

struct StructMembers *
simulator_struct_members (register const char *str, register size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 13,
      MIN_WORD_LENGTH = 3,
      MAX_WORD_LENGTH = 16,
      MIN_HASH_VALUE = 3,
      MAX_HASH_VALUE = 17
    };

  static struct StructMembers wordlist[] =
    {
      {""}, {""}, {""},
      {"Syn", 0, members_Syn},
      {"Plot", 0, members_Plot},
      {"Fiber", 0, members_Fiber},
      {"Target", 0, members_Target},
      {"SynType", 0, members_SynType},
      {"FiberPop", 0, members_FiberPop},
      {"TargetPop", 0, members_TargetPop},
      {"Slice", 0, members_Slice},
      {""},
      {"Network", 0, members_Network},
      {""},
      {"Cell", 0, members_Cell},
      {"LEARN", 0, members_LEARN},
      {"simulator_global", 0, members_simulator_global},
      {"CellPop", 0, members_CellPop}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register unsigned int key = mhash (str, len);

      if (key <= MAX_HASH_VALUE)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strcmp (str + 1, s + 1))
            return &wordlist[key];
        }
    }
  return 0;
}

