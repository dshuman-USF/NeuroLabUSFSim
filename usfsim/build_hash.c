/* ANSI-C code produced by gperf version 3.1 */
/* Command-line: gperf -k '*' -t -E -N inode_struct_info -H ihash  */

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
#include "inode.h"
#include "stddef.h"
#include "string.h"
static int _d0[] = {(5 * 20),0};
struct StructInfo;
/* maximum key range = 407, duplicates = 0 */

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
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538,   0, 538, 538,  45,
       10, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538,   5,   5,   5,   0, 110,
        0,   5, 538,  40, 538,   0,   0, 538, 110,   0,
      538, 538,   0, 120,   0,   0, 538,   0,   0, 538,
      538, 538, 538, 538, 538,   0, 538,   0,  45,   0,
        0,   5,   0,   0,  55,   0,  10,  80,   0,   5,
       25,  10,   5,  95,   0,   0,   0,  20,  50, 538,
       80,  45,  40, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538, 538, 538, 538, 538,
      538, 538, 538, 538, 538, 538
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[39]];
      /*FALLTHROUGH*/
      case 39:
        hval += asso_values[(unsigned char)str[38]];
      /*FALLTHROUGH*/
      case 38:
        hval += asso_values[(unsigned char)str[37]];
      /*FALLTHROUGH*/
      case 37:
        hval += asso_values[(unsigned char)str[36]];
      /*FALLTHROUGH*/
      case 36:
        hval += asso_values[(unsigned char)str[35]];
      /*FALLTHROUGH*/
      case 35:
        hval += asso_values[(unsigned char)str[34]];
      /*FALLTHROUGH*/
      case 34:
        hval += asso_values[(unsigned char)str[33]];
      /*FALLTHROUGH*/
      case 33:
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
inode_struct_info (register const char *str, register size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 155,
      MIN_WORD_LENGTH = 12,
      MAX_WORD_LENGTH = 40,
      MIN_HASH_VALUE = 131,
      MAX_HASH_VALUE = 537
    };

  static struct StructInfo wordlist[] =
    {
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""},
      {"inode_global.doc_file", offsetof (inode_global,doc_file), ato_char_string, str_char_string, 0, 0, sizeof (char), 1024, 0, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
      {"inode_global.inode", offsetof (inode_global,inode), 0, 0, "I_NODE", 0, sizeof (I_NODE), 100, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""},
      {"AXON.y_coord", offsetof (AXON,y_coord), ato_short, str_short, 0, 0, sizeof (short), 15, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_AXON.y_coord", offsetof (OLD_AXON,y_coord), ato_short, str_short, 0, 0, sizeof (short), 15, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"AXON.num_coords", offsetof (AXON,num_coords), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_AXON.num_coords", offsetof (OLD_AXON,num_coords), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"inode_global.malloc_debug", offsetof (inode_global,malloc_debug), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"inode_global.presynaptic_flag", offsetof (inode_global,presynaptic_flag), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""},
      {"inode_global.num_free_nodes", offsetof (inode_global,num_free_nodes), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"AXON.x_coord", offsetof (AXON,x_coord), ato_short, str_short, 0, 0, sizeof (short), 15, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_AXON.x_coord", offsetof (OLD_AXON,x_coord), ato_short, str_short, 0, 0, sizeof (short), 15, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""},
      {"inode_global.num_used_nodes", offsetof (inode_global,num_used_nodes), ato_int, str_int, 0, 0, sizeof (int), 50, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"F_NODE.f_targets", offsetof (F_NODE,f_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.f_seed", offsetof (F_NODE,f_seed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_targets", offsetof (OLD_F_NODE,f_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_targets", offsetof (C_NODE,c_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_F_NODE.f_seed", offsetof (OLD_F_NODE,f_seed), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"OLD_C_NODE.c_targets", offsetof (OLD_C_NODE,c_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.f_pop", offsetof (F_NODE,f_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"F_NODE.f_target_seed", offsetof (F_NODE,f_target_seed), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_F_NODE.f_pop", offsetof (OLD_F_NODE,f_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_pop", offsetof (C_NODE,c_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_target_seed", offsetof (OLD_F_NODE,f_target_seed), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_target_seed", offsetof (C_NODE,c_target_seed), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_pop", offsetof (OLD_C_NODE,c_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.f_end", offsetof (F_NODE,f_end), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_target_seed", offsetof (OLD_C_NODE,c_target_seed), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_end", offsetof (OLD_F_NODE,f_end), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.group", offsetof (F_NODE,group), ato_char_string, str_char_string, 0, 0, sizeof (char), 64, 0, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""},
      {"C_NODE.c_accom_param", offsetof (C_NODE,c_accom_param), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.group", offsetof (C_NODE,group), ato_char_string, str_char_string, 0, 0, sizeof (char), 64, 0, 0, 0, 0, 0, 0, 1, 1},
      {"F_NODE.f_terminals", offsetof (F_NODE,f_terminals), ato_short, str_short, 0, 0, sizeof (short), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_accom_param", offsetof (OLD_C_NODE,c_accom_param), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.ilm_elm_fr", offsetof (GLOBAL_NETWORK,ilm_elm_fr), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.total_cells", offsetof (GLOBAL_NETWORK,total_cells), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_F_NODE.f_terminals", offsetof (OLD_F_NODE,f_terminals), ato_short, str_short, 0, 0, sizeof (short), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_terminals", offsetof (C_NODE,c_terminals), ato_short, str_short, 0, 0, sizeof (short), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_GLOBAL_NETWORK.total_cells", offsetof (OLD_GLOBAL_NETWORK,total_cells), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"U_NODE.cell_node", offsetof (U_NODE,cell_node), 0, 0, "C_NODE", 0, sizeof (C_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_terminals", offsetof (OLD_C_NODE,c_terminals), ato_short, str_short, 0, 0, sizeof (short), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"inode_global.file_subversion", offsetof (inode_global,file_subversion), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_U_NODE.cell_node", offsetof (OLD_U_NODE,cell_node), 0, 0, "OLD_C_NODE", 0, sizeof (OLD_C_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"C_NODE.cell_y", offsetof (C_NODE,cell_y), ato_short, str_short, 0, 0, sizeof (short), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.c_dc_injected", offsetof (C_NODE,c_dc_injected), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"F_NODE.f_prob", offsetof (F_NODE,f_prob), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_dc_injected", offsetof (OLD_C_NODE,c_dc_injected), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.f_target_nums", offsetof (F_NODE,f_target_nums), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_prob", offsetof (OLD_F_NODE,f_prob), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_target_nums", offsetof (OLD_F_NODE,f_target_nums), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_target_nums", offsetof (C_NODE,c_target_nums), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"inode_global.baby_lung_flag", offsetof (inode_global,baby_lung_flag), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_target_nums", offsetof (OLD_C_NODE,c_target_nums), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.c_accomodation", offsetof (C_NODE,c_accomodation), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_mem_potential", offsetof (C_NODE,c_mem_potential), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.f_begin", offsetof (F_NODE,f_begin), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_accomodation", offsetof (OLD_C_NODE,c_accomodation), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_mem_potential", offsetof (OLD_C_NODE,c_mem_potential), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_begin", offsetof (OLD_F_NODE,f_begin), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.step_size", offsetof (GLOBAL_NETWORK,step_size), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_GLOBAL_NETWORK.step_size", offsetof (OLD_GLOBAL_NETWORK,step_size), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"GLOBAL_NETWORK.total_fibers", offsetof (GLOBAL_NETWORK,total_fibers), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.cell_x", offsetof (C_NODE,cell_x), ato_short, str_short, 0, 0, sizeof (short), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"OLD_GLOBAL_NETWORK.total_fibers", offsetof (OLD_GLOBAL_NETWORK,total_fibers), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"U_NODE.fiber_node", offsetof (U_NODE,fiber_node), 0, 0, "F_NODE", 0, sizeof (F_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.fiber_y", offsetof (F_NODE,fiber_y), ato_short, str_short, 0, 0, sizeof (short), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_U_NODE.fiber_node", offsetof (OLD_U_NODE,fiber_node), 0, 0, "OLD_F_NODE", 0, sizeof (OLD_F_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"I_NODE.unode", offsetof (I_NODE,unode), 0, 0, "U_NODE", 0, sizeof (U_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"U_NODE.global_node", offsetof (U_NODE,global_node), 0, 0, "GLOBAL_NETWORK", 0, sizeof (GLOBAL_NETWORK), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_ap_k_delta", offsetof (C_NODE,c_ap_k_delta), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"I_NODE.comment2", offsetof (I_NODE,comment2), ato_char_string, str_char_string, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 1, 1},
      {"OLD_I_NODE.unode", offsetof (OLD_I_NODE,unode), 0, 0, "OLD_U_NODE", 0, sizeof (OLD_U_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_U_NODE.global_node", offsetof (OLD_U_NODE,global_node), 0, 0, "OLD_GLOBAL_NETWORK", 0, sizeof (OLD_GLOBAL_NETWORK), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_ap_k_delta", offsetof (OLD_C_NODE,c_ap_k_delta), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_I_NODE.comment2", offsetof (OLD_I_NODE,comment2), ato_char, str_char, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.f_min_conduct_time", offsetof (F_NODE,f_min_conduct_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"F_NODE.f_conduction_time", offsetof (F_NODE,f_conduction_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_min_conduct_time", offsetof (C_NODE,c_min_conduct_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"OLD_F_NODE.f_conduction_time", offsetof (OLD_F_NODE,f_conduction_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_conduction_time", offsetof (C_NODE,c_conduction_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.sim_length", offsetof (GLOBAL_NETWORK,sim_length), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.max_targets", offsetof (GLOBAL_NETWORK,max_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.total_populations", offsetof (GLOBAL_NETWORK,total_populations), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_conduction_time", offsetof (OLD_C_NODE,c_conduction_time), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_GLOBAL_NETWORK.sim_length", offsetof (OLD_GLOBAL_NETWORK,sim_length), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_GLOBAL_NETWORK.max_targets", offsetof (OLD_GLOBAL_NETWORK,max_targets), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_GLOBAL_NETWORK.total_populations", offsetof (OLD_GLOBAL_NETWORK,total_populations), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"U_NODE.synapse_node", offsetof (U_NODE,synapse_node), 0, 0, "S_NODE", 0, sizeof (S_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.cell_axon", offsetof (C_NODE,cell_axon), 0, 0, "AXON", 0, sizeof (AXON), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_rebound_param", offsetof (C_NODE,c_rebound_param), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_U_NODE.synapse_node", offsetof (OLD_U_NODE,synapse_node), 0, 0, "OLD_S_NODE", 0, sizeof (OLD_S_NODE), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.fiber_x", offsetof (F_NODE,fiber_x), ato_short, str_short, 0, 0, sizeof (short), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.cell_axon", offsetof (OLD_C_NODE,cell_axon), 0, 0, "OLD_AXON", 0, sizeof (OLD_AXON), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_rebound_param", offsetof (OLD_C_NODE,c_rebound_param), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"GLOBAL_NETWORK.global_comment", offsetof (GLOBAL_NETWORK,global_comment), ato_char_string, str_char_string, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 1, 1},
      {"I_NODE.comment1", offsetof (I_NODE,comment1), ato_char_string, str_char_string, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 1, 1},
      {"I_NODE.node_type", offsetof (I_NODE,node_type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_GLOBAL_NETWORK.global_comment", offsetof (OLD_GLOBAL_NETWORK,global_comment), ato_char, str_char, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_I_NODE.comment1", offsetof (OLD_I_NODE,comment1), ato_char, str_char, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_I_NODE.node_type", offsetof (OLD_I_NODE,node_type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.f_synapse_type", offsetof (F_NODE,f_synapse_type), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.pop_subtype", offsetof (F_NODE,pop_subtype), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.f_synapse_type", offsetof (OLD_F_NODE,f_synapse_type), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_synapse_type", offsetof (C_NODE,c_synapse_type), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.pop_subtype", offsetof (C_NODE,pop_subtype), ato_char, str_char, 0, 0, sizeof (char), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_synapse_type", offsetof (OLD_C_NODE,c_synapse_type), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_constant_ika", offsetof (C_NODE,c_constant_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"S_NODE.parent", offsetof (S_NODE,parent), ato_int, str_int, 0, 0, sizeof (int), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_constant_ika", offsetof (OLD_C_NODE,c_constant_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.freq_type", offsetof (F_NODE,freq_type), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.c_resting_thresh", offsetof (C_NODE,c_resting_thresh), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"C_NODE.c_resting_thresh_sd", offsetof (C_NODE,c_resting_thresh_sd), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_resting_thresh", offsetof (OLD_C_NODE,c_resting_thresh), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.sim_length_seconds", offsetof (GLOBAL_NETWORK,sim_length_seconds), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.c_pro_activate_ika", offsetof (C_NODE,c_pro_activate_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"F_NODE.fiber_axon", offsetof (F_NODE,fiber_axon), 0, 0, "AXON", 0, sizeof (AXON), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_pro_activate_ika", offsetof (OLD_C_NODE,c_pro_activate_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_F_NODE.fiber_axon", offsetof (OLD_F_NODE,fiber_axon), 0, 0, "OLD_AXON", 0, sizeof (OLD_AXON), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_pro_deactivate_ika", offsetof (C_NODE,c_pro_deactivate_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"F_NODE.f_synapse_strength", offsetof (F_NODE,f_synapse_strength), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_pro_deactivate_ika", offsetof (OLD_C_NODE,c_pro_deactivate_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_k_conductance", offsetof (C_NODE,c_k_conductance), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"F_NODE.fuzzy_range", offsetof (F_NODE,fuzzy_range), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_F_NODE.f_synapse_strength", offsetof (OLD_F_NODE,f_synapse_strength), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"C_NODE.c_synapse_strength", offsetof (C_NODE,c_synapse_strength), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_k_conductance", offsetof (OLD_C_NODE,c_k_conductance), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"I_NODE.node_number", offsetof (I_NODE,node_number), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_synapse_strength", offsetof (OLD_C_NODE,c_synapse_strength), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"GLOBAL_NETWORK.maximum_cells_per_pop", offsetof (GLOBAL_NETWORK,maximum_cells_per_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_I_NODE.node_number", offsetof (OLD_I_NODE,node_number), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"OLD_GLOBAL_NETWORK.maximum_cells_per_pop", offsetof (OLD_GLOBAL_NETWORK,maximum_cells_per_pop), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"C_NODE.c_injected_expression", offsetof (C_NODE,c_injected_expression), ato_char_star, str_char_star, 0, 0, sizeof (char), 1, 1, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""},
      {"F_NODE.frequency", offsetof (F_NODE,frequency), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"S_NODE.s_time_constant", offsetof (S_NODE,s_time_constant), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_S_NODE.s_time_constant", offsetof (OLD_S_NODE,s_time_constant), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"C_NODE.c_rebound_time_k", offsetof (C_NODE,c_rebound_time_k), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_C_NODE.c_rebound_time_k", offsetof (OLD_C_NODE,c_rebound_time_k), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""},
      {"GLOBAL_NETWORK.num_synapse_types", offsetof (GLOBAL_NETWORK,num_synapse_types), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"GLOBAL_NETWORK.max_conduction_time", offsetof (GLOBAL_NETWORK,max_conduction_time), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_GLOBAL_NETWORK.num_synapse_types", offsetof (OLD_GLOBAL_NETWORK,num_synapse_types), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_GLOBAL_NETWORK.max_conduction_time", offsetof (OLD_GLOBAL_NETWORK,max_conduction_time), ato_int, str_int, 0, 0, sizeof (int), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""}, {""}, {""}, {""}, {""}, {""},
      {"S_NODE.synapse_name", offsetof (S_NODE,synapse_name), ato_char_string, str_char_string, 0, _d0, sizeof (char), 32, 0, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""}, {""},
      {"OLD_S_NODE.synapse_name", offsetof (OLD_S_NODE,synapse_name), ato_char, str_char, 0, _d0, sizeof (char), 32, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"S_NODE.syn_type", offsetof (S_NODE,syn_type), ato_char, str_char, 0, 0, sizeof (char), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"GLOBAL_NETWORK.lumbar_equation", offsetof (GLOBAL_NETWORK,lumbar_equation), ato_char_string, str_char_string, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {""},
      {"C_NODE.c_thresh_active_ika", offsetof (C_NODE,c_thresh_active_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"C_NODE.c_max_conductance_ika", offsetof (C_NODE,c_max_conductance_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""},
      {"OLD_C_NODE.c_thresh_active_ika", offsetof (OLD_C_NODE,c_thresh_active_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {"S_NODE.s_eq_potential", offsetof (S_NODE,s_eq_potential), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"OLD_C_NODE.c_max_conductance_ika", offsetof (OLD_C_NODE,c_max_conductance_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""},
      {"OLD_S_NODE.s_eq_potential", offsetof (OLD_S_NODE,s_eq_potential), ato_float, str_float, 0, 0, sizeof (float), (5 * 20), 0, 0, 0, 0, 0, 0, 0, 1},
      {"GLOBAL_NETWORK.phrenic_equation", offsetof (GLOBAL_NETWORK,phrenic_equation), ato_char_string, str_char_string, 0, 0, sizeof (char), 100, 0, 0, 0, 0, 0, 0, 1, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"C_NODE.c_thresh_remove_ika", offsetof (C_NODE,c_thresh_remove_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_C_NODE.c_thresh_remove_ika", offsetof (OLD_C_NODE,c_thresh_remove_ika), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""}, {""}, {""}, {""}, {""},
      {"GLOBAL_NETWORK.k_equilibrium", offsetof (GLOBAL_NETWORK,k_equilibrium), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1},
      {""}, {""}, {""},
      {"OLD_GLOBAL_NETWORK.k_equilibrium", offsetof (OLD_GLOBAL_NETWORK,k_equilibrium), ato_float, str_float, 0, 0, sizeof (float), 1, 0, 0, 0, 0, 0, 0, 0, 1}
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
/* Command-line: gperf -k '*' -t -E -N inode_struct_members -H mhash  */

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


char *members_AXON[] = {
    "num_coords",
    "x_coord",
    "y_coord",
    0
};
char *members_GLOBAL_NETWORK[] = {
    "total_populations",
    "total_fibers",
    "total_cells",
    "sim_length",
    "k_equilibrium",
    "max_conduction_time",
    "num_synapse_types",
    "max_targets",
    "step_size",
    "maximum_cells_per_pop",
    "global_comment",
    "phrenic_equation",
    "lumbar_equation",
    "ilm_elm_fr",
    "sim_length_seconds",
    0
};
char *members_F_NODE[] = {
    "fiber_x",
    "fiber_y",
    "fiber_axon",
    "f_prob",
    "f_begin",
    "f_end",
    "f_seed",
    "f_pop",
    "f_targets",
    "group",
    "f_target_nums",
    "f_min_conduct_time",
    "f_conduction_time",
    "f_terminals",
    "f_synapse_type",
    "f_synapse_strength",
    "f_target_seed",
    "pop_subtype",
    "freq_type",
    "frequency",
    "fuzzy_range",
    0
};
char *members_C_NODE[] = {
    "cell_x",
    "cell_y",
    "cell_axon",
    "c_accomodation",
    "c_k_conductance",
    "c_mem_potential",
    "c_resting_thresh",
    "c_resting_thresh_sd",
    "c_ap_k_delta",
    "c_accom_param",
    "c_pop",
    "c_targets",
    "group",
    "c_target_nums",
    "c_min_conduct_time",
    "c_conduction_time",
    "c_terminals",
    "c_synapse_type",
    "c_synapse_strength",
    "c_target_seed",
    "c_rebound_param",
    "c_rebound_time_k",
    "c_thresh_remove_ika",
    "c_thresh_active_ika",
    "c_max_conductance_ika",
    "c_pro_deactivate_ika",
    "c_pro_activate_ika",
    "c_constant_ika",
    "c_dc_injected",
    "c_injected_expression",
    "pop_subtype",
    0
};
char *members_S_NODE[] = {
    "synapse_name",
    "s_eq_potential",
    "s_time_constant",
    "syn_type",
    "parent",
    0
};
char *members_OLD_AXON[] = {
    "num_coords",
    "x_coord",
    "y_coord",
    0
};
char *members_OLD_GLOBAL_NETWORK[] = {
    "total_populations",
    "total_fibers",
    "total_cells",
    "sim_length",
    "k_equilibrium",
    "max_conduction_time",
    "num_synapse_types",
    "max_targets",
    "step_size",
    "maximum_cells_per_pop",
    "global_comment",
    0
};
char *members_OLD_F_NODE[] = {
    "fiber_axon",
    "f_prob",
    "f_begin",
    "f_end",
    "f_seed",
    "f_pop",
    "f_targets",
    "f_target_nums",
    "f_conduction_time",
    "f_terminals",
    "f_synapse_type",
    "f_synapse_strength",
    "f_target_seed",
    0
};
char *members_OLD_C_NODE[] = {
    "cell_axon",
    "c_accomodation",
    "c_k_conductance",
    "c_mem_potential",
    "c_resting_thresh",
    "c_ap_k_delta",
    "c_accom_param",
    "c_pop",
    "c_targets",
    "c_target_nums",
    "c_conduction_time",
    "c_terminals",
    "c_synapse_type",
    "c_synapse_strength",
    "c_target_seed",
    "c_rebound_param",
    "c_rebound_time_k",
    "c_thresh_remove_ika",
    "c_thresh_active_ika",
    "c_max_conductance_ika",
    "c_pro_deactivate_ika",
    "c_pro_activate_ika",
    "c_constant_ika",
    "c_dc_injected",
    0
};
char *members_OLD_S_NODE[] = {
    "synapse_name",
    "s_eq_potential",
    "s_time_constant",
    0
};
char *members_OLD_U_NODE[] = {
    "global_node",
    "cell_node",
    "fiber_node",
    "synapse_node",
    0
};
#include "inode_choose.c"
char *members_OLD_I_NODE[] = {
    "node_type",
    "node_number",
    "comment1",
    "comment2",
    "unode",
    0
};
char *members_U_NODE[] = {
    "global_node",
    "cell_node",
    "fiber_node",
    "synapse_node",
    0
};
char *members_I_NODE[] = {
    "node_type",
    "node_number",
    "comment1",
    "comment2",
    "unode",
    0
};
char *members_inode_global[] = {
    "file_subversion",
    "malloc_debug",
    "doc_file",
    "inode",
    "num_used_nodes",
    "num_free_nodes",
    "presynaptic_flag",
    "baby_lung_flag",
    0
};
struct StructMembers;
/* maximum key range = 22, duplicates = 0 */

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
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26,  0,  0,  3,  0,  0,
      15,  0, 26, 10, 26,  0,  0, 26,  0,  0,
      26, 26,  0,  5,  0,  0, 26,  0,  0, 26,
      26, 26, 26, 26, 26,  0, 26,  0,  0, 26,
       0,  0, 26,  0, 26,  0, 26, 26,  0, 26,
       0,  0, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
      26, 26, 26, 26, 26, 26
    };
  register unsigned int hval = len;

  switch (hval)
    {
      default:
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

struct StructMembers *
inode_struct_members (register const char *str, register size_t len)
{
  enum
    {
      TOTAL_KEYWORDS = 15,
      MIN_WORD_LENGTH = 4,
      MAX_WORD_LENGTH = 18,
      MIN_HASH_VALUE = 4,
      MAX_HASH_VALUE = 25
    };

  static struct StructMembers wordlist[] =
    {
      {""}, {""}, {""}, {""},
      {"AXON", 0, members_AXON},
      {""},
      {"U_NODE", choose_U_NODE, members_U_NODE},
      {""},
      {"OLD_AXON", 0, members_OLD_AXON},
      {"C_NODE", 0, members_C_NODE},
      {"OLD_U_NODE", choose_OLD_U_NODE, members_OLD_U_NODE},
      {"S_NODE", 0, members_S_NODE},
      {"inode_global", 0, members_inode_global},
      {"OLD_C_NODE", 0, members_OLD_C_NODE},
      {"GLOBAL_NETWORK", 0, members_GLOBAL_NETWORK},
      {"OLD_S_NODE", 0, members_OLD_S_NODE},
      {"I_NODE", 0, members_I_NODE},
      {""},
      {"OLD_GLOBAL_NETWORK", 0, members_OLD_GLOBAL_NETWORK},
      {""},
      {"OLD_I_NODE", 0, members_OLD_I_NODE},
      {"F_NODE", 0, members_F_NODE},
      {""}, {""}, {""},
      {"OLD_F_NODE", 0, members_OLD_F_NODE}
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

