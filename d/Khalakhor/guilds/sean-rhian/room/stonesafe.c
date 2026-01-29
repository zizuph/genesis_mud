/* Safe room
**   This room is never entered by mortals. It is a holding area for
**   NPCs who have turned themselves into stone. See npc/nov_specatck
**   and obj/safestatue
**
** History:
** Date        Coder       Action
**----------   ----------- ----------------------------------
** 1/6/98       Zima        Created
**
*/
/* inherits/includes */
inherit  "/d/Khalakhor/std/room";
 
/* room definition */
void create_khalakhor_room() {
   set_short("a safe room");
   set_long("   A magical safe room. If you are a player, you shouldn't "+
            "be here!\n");
}
