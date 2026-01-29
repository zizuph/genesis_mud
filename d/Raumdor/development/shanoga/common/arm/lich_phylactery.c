/* 
 * This is the part of the lich's artifact that will be on its body before
 * the player kills him and collects it. It provides a small boost to life
 * spells until it is cleansed in Drakmere.
 *
 * Worn By: /d/Raumdor/common/npc/lich.c
 *
 * Updated 2018.03.28 (Shanoga)
 */

inherit "/std/armour.c";
#include "defs.h"

#define SKILL_TYPE          SS_ELEMENT_LIFE
#define SKILL_AMOUNT        10

int bonus_skill;

/*
 * Function name: create_armour
 * Description  : The masked create routine
 */
void
create_armour()
{
    ::create_armour();
    set_name("phylactery");
    set_adj("immaculate");
    set_short("immaculate phylactery");
    add_name("box");
    set_long("This small box is carved out of marble and affixed to a " +
      "chain so it can be worn around the neck. It is finely crafted and " +
      "covered in elaborate carvings. It is immaculately clean and even " +
      "the crevices within the intricate carvings are free of dirt, dust, " +
      "and grime. The box is lightweight and something is rolling around " +
      "the inside.\n");

    set_at(A_NECK);
    set_ac(1);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
    add_prop(MAGIC_AM_MAGIC,({30, "life"}));
    add_prop(MAGIC_AM_ID_INFO,({
      "This amulet enhances the magic of life itself.\n", 20,
      "The wearer of this phylalctery will have increased mastery of life" +
        "magic.\n", 40,
      "The magic within can be realized and expanded in Drakmere.\n",50}));
    add_prop(OBJ_S_WIZINFO,"This phylactery can be taken to the throne " +
      "room in Drakmere where Drakin can cleanse it and the original " +
      "nature can be restored. The only magical aspect of the box now is " +
      "a small boost to life spells.\n");
    add_prop(OBJ_I_WEIGHT,200);
    add_prop(OBJ_I_VOLUME,400);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_BUY,1);
}

/*
 * Function name: wear
 * Description  : Adds the bonus skill and special description when the
 *              : phylactery is worn
 * Arguments    : object ob - the phylactery
 */
int
wear(object ob)
{
    E(TO)->set_skill_extra(SKILL_TYPE,
      E(TO)->query_skill_extra(SKILL_TYPE) + SKILL_AMOUNT);
    TELL(E(TO),"As you lift the chain over your head, the phylactery rests " +
      "lightly on your chest and the touch of the chain on your neck " +
      "sends an invigorating shiver throughout your body.\n");
    return 1;
}

/*
 * Function name: remove
 * Description  : Removes the bonus skill and special description when
 *              : the phylactery is removed
 * Arguments    : object ob - the phylactery
 */
int
remove(object ob)
{
    E(TO)->set_skill_extra(SKILL_TYPE,
      E(TO)->query_skill_extra(SKILL_TYPE) - SKILL_AMOUNT);
    TELL(E(TO),"The invigorating feeling passes from you as you lift the chain " +
      "from your neck and remove the box from your chest.\n");
    return 1;
}