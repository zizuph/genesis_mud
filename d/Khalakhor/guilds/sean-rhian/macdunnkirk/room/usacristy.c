/* Abbey - Sacristy of the Upper Level - shop to buy guild items (no sell)
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 4/10/98     Zima        Created
** 6/22/98     Zima        Updated
*/
/* inherits/includes */
#include <stdproperties.h>
#include "defs.h"
inherit SR_ROOM+"shopbase";
 
void reset_room ()
{
   reset_keeper(SR_NPC+"sithehenn");
}
 
/* room definition */
void create_khalakhor_room()
{
   set_short("Sacristy of the abbey");
   set_long(
       "   You are in the sacristy of the abbey, where the many items used "+
       "by the saggarts and manachs are kept. There are five tall cabinets "+
       "standing along the walls, each filled with various vestments, "+
       "accessories, ritualistic tools, staffs and supplies. A small "+
       "chandelier hangs from the ceiling, while there is a window on "+
       "the western wall.\n");
 
   INSIDE;
   add_item(({"sacristy","chamber","room"}),
       "It is a simple chamber of stone, nothing ornate.\n");
 
   add_item("window",
       "The window is tall and thin, its top rising to a "+
       "pointed arch. It is set in the western wall of the chamber, "+
       "its opaque pane a lattice of diamond shaped pieces of a "+
       "cream color.\n");
 
   add_item(({"candles","chandelier","ceiling"}),
       "There is a large golden chandelier handing from the ceiling, "+
       "filled with small candles which are placed in holders around the "+
       "chandelier's circumference. They provide a good deal of light.\n");
 
   add_item(({"sign","list","price","prices"}),
       "You don't see any, but perhaps you could ask someone.\n");
 
   add_item(({"cabinet","cabinets"}),
       "There are five large cabinets standing along the walls, each made "+
       "of sturdy oak with crystal doors so that you can see the items "+
       "inside. They seem to be locked, or at least enchanted, as you "+
       "cower at the thought of trying to open or unlock them. Their "+
       "treasures are obviously of high price. You could get a better "+
       "view of each if you examined each one, the first through the "+
       "fifth.\n");
 
   add_cmd_item(({"cabinet","cabinets"}),({"unlock","open"}),
       "A mysterious force prevents you from doing that.\n");
 
   add_item(({"first cabinet","vestments"}),
       "The first cabinet contains a colorful array of vestments hanging "+
       "neatly from a pole including purple and white robes, lace surplices, "+
       "black cassocks, and purple copes, dalmatics, and chasubles.\n");
 
   add_item(({"second cabinet","accessories"}),
       "The shelves of the second cabinet are filled with various "+
       "accessories which are worn including stoles, tonsures, cinctures, "+
       "sashes, copes and mitres, all available in purple or white, along "+
       "with ornate gold shawls.\n");
 
   add_item(({"third cabinet","tools"}),
       "The third cabinet contains various tools used in the rites "+
       "performed by the saggarts and manachs. There are monstrances, "+
       "chalices, censors, mortars, pestles and candlesticks.\n");
 
   add_item(({"fourth cabinet","staffs","croziers"}),
       "The fourth cabinet contains a selection of wooden staffs, varying "+
       "through rough, polished, carved and ornate. Tall croziers of "+
       "brass, silver and gold are also stored in the fourth cabinet.\n");
 
   add_item(({"fifth cabinet","supplies"}),
       "The shelves of the fifth cabinet are filled with various "+
       "supplies including empty vials, empty oil flasks, herb pouches "+
       "and cakes of incense.\n");
 
   /* exits */
   add_exit("ucorr4","east");
   reset_room();
 
   set_item_list (
      ({
      // first cabinet - vestments
      ({"[white] 'robe'",            SR_ARMOUR+"robe",       100, 30}),
      ({"[purple] 'robe'",           SR_ARMOUR+"probe",      100, 10}),
      ({"[purple] 'chasuble'",       SR_ARMOUR+"chasuble",   225, 40}),
      ({"[purple] 'dalmatic'",       SR_ARMOUR+"dalmatic",   225, 30}),
      ({"[white] [lace] 'surplice'", SR_ARMOUR+"surplice",    75, 12}),
      ({"[black] 'cassock'",         SR_ARMOUR+"cassock",    125, 20}),
 
      // second cabinet - accessories
      ({"[purple] 'stole'",          SR_ARMOUR+"stole",     50,   22}),
      ({"[purple] 'tonsure'",        SR_ARMOUR+"tonsure",   25,   13}),
      ({"[purple] 'cincture'",       SR_ARMOUR+"cincture",  30,   30}),
      ({"[purple] 'sash'",           SR_ARMOUR+"sash",      30,   21}),
      ({"[purple] 'cope'",           SR_ARMOUR+"cope",      100,  20}),
      ({"[purple] 'mitre'",          SR_ARMOUR+"mitre",     50,   51}),
      ({"[white] 'stole'",           SR_ARMOUR+"wstole",    50,   53}),
      ({"[white] 'tonsure'",         SR_ARMOUR+"wtonsure",  25,   50}),
      ({"[white] 'cincture'",        SR_ARMOUR+"wcincture", 30,   11}),
      ({"[white] 'sash'",            SR_ARMOUR+"wsash",     30,   50}),
      ({"[white] 'cope'",            SR_ARMOUR+"wcope",     100,  52}),
      ({"[white] 'mitre'",           SR_ARMOUR+"wmitre",    50,   52}),
      ({"[ornate] [gold] 'shawl'",   SR_ARMOUR+"monshawl",  150,  40}),
 
      // third cabinet - tools
      ({"[gold] 'monstrance'",       SR_TOOL+"monstrance",  350,  40}),
      ({"[gold] 'chalice'",          SR_TOOL+"chalice",     100,  30}),
      ({"[gold] 'platter'",          SR_TOOL+"gplatter",    100,  30}),
      ({"[silver] 'censor'",         SR_TOOL+"censor",      125,  30}),
      ({"[ceramic] 'mortar'",        SR_TOOL+"cmortar",     720,  10}),
      ({"[ceramic] 'pestle'",        SR_TOOL+"pestle",       75,  10}),
      ({"[gold] 'candlestick'",      SR_TOOL+"candlestick", 120,  10}),
 
      // fourth cabinet - staffs and croziers
      ({"[rough] [wooden] 'staff'",  SR_WEAPON+"nstaff",    350,  10}),
      ({"[polished] [wooden] 'staff'",SR_WEAPON+"sstaff",   350,  20}),
      ({"[carved] [wooden] 'staff'", SR_WEAPON+"dstaff",    350,  30}),
      ({"[ornate] [wooden] 'staff'", SR_WEAPON+"pstaff",    350,  40}),
      ({"[brass] 'crozier'",         SR_WEAPON+"bcrozier",  350,  50}),
      ({"[silver] 'crozier'",        SR_WEAPON+"scrozier",  350,  51}),
      ({"[gold] 'crozier'",          SR_WEAPON+"gcrozier",  350,  52}),
 
      // fifth cabinet - supplies
      ({"[glass] 'vial'",            SR_TOOL+"hwvial",        6,  10}),
      ({"[glass] 'flask'",           SR_TOOL+"flask",        12,  10}),
      ({"[herb] 'pouch'",            SR_TOOL+"hpouch",       120, 10}),
      ({"[cake] [of] [incense]",     SR_OBJ+"cake_incense",   50, 30})
      }));
}
