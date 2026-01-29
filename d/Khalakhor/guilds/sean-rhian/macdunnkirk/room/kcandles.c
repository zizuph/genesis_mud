/* Kirk Abbey - Candle Shop
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 7/25/97     Zima        Created
** 4/12/98     Zima        Recoded to inherit shopbase
** 5/26/98     Zima        Added candlewaught object; part of entrance quest
**
*/
/* inherits/includes */
#include "defs.h"
inherit  SR_ROOM+"shopbase";
#define  PRICE 40
object   cwraught;
 
void reset_room()
{
   reset_keeper(SR_NPC+"seandlar");
   if ((!objectp(cwraught))||(!present(cwraught,TO)))
      {
      cwraught = clone_object(SR_TOOL+"cwraught");
      cwraught->move(TO);
      }
}
 
/* room definition */
void create_khalakhor_room()
{
   set_short("Candleworks of the abbey");
   set_long(
       "   The sweet smell of perfumes and dyes mingle with that of hot "+
       "wax, filling this chamber with an enchanting aroma. This is "+
       "the candleworks of the abbey where the manachs make the "+
       "hundreds of candles used fill the dozens of chandeliers and "+
       "for their rites. Ornate candles line shelves along the north "+
       "wall set with various colors and symbols. There is a sign on "+
       "the wall.\n");
 
   add_item(({"perfumes","dyes"}),
      "Some of the ingredients of the candles, their aroma fills "+
      "the chamber.\n");
   add_item("candles",
      "Several ornate candles cast in various sizes, shapes and "+
      "colors sit along the shelves. Some are molded into various "+
      "forms. Unfortunately, they are not for sale.\n");
   add_item("shelves",
      "Placed along the north wall, they hold ornate candles of "+
      "various shapes and sizes.\n");
   add_item("sign","A simple sign on the wall. You can read it.\n");
   add_cmd_item("sign","read",
      "+-------------------------+\n"+
      "| Common Beeswax Candles  |\n"+
      "|          "+PRICE+" cc          |\n"+
      "+-------------------------+\n");
 
   /* exits */
   add_exit("kcorr4","east");
   reset_room();
   set_item_list(
      ({
         ({"[common] [beeswax] 'candle'", SR_OBJ+"cbwcandle",PRICE,0})
      }));
}
 
void init()
{
   ::init();
   add_action(&buy(),"buy");
}
