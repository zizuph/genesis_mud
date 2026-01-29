/*
 * "Nice to have"-macros:
 */

#define WRAP(STR) word_wrap_with_paragraphs(STR)

#define NATIVE_RACES    ({ "elf" })
#define IS_NATIVE(P)    (member_array(P->query_race_name(), NATIVE_RACES) >= 0)

#define N_KNOW(NATIVE, FOREIGN) ("@@native_knowledge|"+NATIVE+"|"+FOREIGN+"@@")
#define N_OBS( NATIVE, FOREIGN) ("@@native_knowledge|"+NATIVE+"|"+FOREIGN+"@@")

#define DPHRASE(LABEL)          ("@@dir_phrase|" + LABEL + "@@")
#define NYI  "@@block_exit_temporarily@@"

#define H_ITEM(ID, PRESENT, ABSENT) \
  ("@@hidden_item_desc|" + ID + "|" + PRESENT  + "|" + ABSENT   + "@@")
#define GET_H_ITEM(ID, SUCC_MSG, FAIL_MSG) \
  ("@@get_hidden_item|"  + ID + "|" + SUCC_MSG + "|" + FAIL_MSG + "@@") 

/*
 * Standard directories:
 */

#define ROOMDIR     "/d/Genesis/start/elf/room/"
#define MONSTERDIR  "/d/Genesis/start/elf/monster/"
#define OBJDIR      "/d/Genesis/start/elf/obj/"
#define BBOARDDIR   "/d/Genesis/start/elf/bboard"
#define LOGDIR      "/d/Genesis/start/elf/log/"

#define POSTDIR     "/d/Genesis/post_dir/"

/*
 * Linkage to the world:
 */

#define ENTRANCE_LOCATION "/d/Genesis/start/elf/glade"

/*
 * Who maintains the code?
 */

#define MAINTAINER "caution"

/*
 * standard objects:
 */

#define OBJECT      "/std/object"
#define ELFROOM     "/d/Genesis/start/elf/elfroom"
#define ELFAREA     "/d/Genesis/start/elf/elfarea"
#define ELFTERRAIN  "/d/Genesis/start/elf/elfterrain"
#define DIRROOM     "/d/Wiz/caution/open/dir_room"

#define STRINGLIB "d/Genesis/start/elf/lib/string"
#define MISCLIB   "d/Genesis/start/elf/lib/misc"

#define DEPOSITORY "/d/Genesis/start/elf/obj/depository"

#define MAILREADER    "/d/Genesis/obj/mail_reader"
#define MAILREADER_ID "mailread"

#define NOTE "/d/Genesis/elf/obj/note"

/*
 * Terrains:
 */

#define USE_MAP 0
#define TERRAIN_FIR_FOREST "/d/Genesis/start/elf/terrain/fir_forest"
#define CENTER_SQUARE      "/d/Genesis/start/elf/elf_start"
#define CENTER_X 186
#define CENTER_Y 554


#define DIRECTIONS ([      \
 "north":     ({ 0,  1}),  \
 "south":     ({ 0, -1}),  \
 "east":      ({ 1,  0}),  \
 "west":      ({-1,  0}),  \
 "northeast": ({ 1,  1}),  \
 "northwest": ({-1,  1}),  \
 "southeast": ({ 1, -1}),  \
 "southwest": ({-1, -1})   \
])  

/*
 * Properties:
 */

#define STD_WIZINFO \
  add_prop(OBJ_S_WIZINFO, "@@wizinfo:" + file_name(this_object()) + "@@")

#define SAFE_ROOM \
  add_prop(ROOM_I_NO_ATTACK); \
  add_prop(ROOM_I_NO_MAGIC_ATTACK); \
  add_prop(ROOM_I_NO_STEAL)
  
