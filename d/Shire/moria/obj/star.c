/*
 * star.c                                    (C) Sir Rogon, 1994.
 *
 * This is a diamond sprinkled star with an astonnishing feature.
 * You can wave it above something, causing diamond sprinkles to
 * befall the object, causing its price to increase.
 *
 */

inherit "/std/object";

#include "defs.h"

#define IS_SPRINKLED  "_obj_i_moria_is_sprinkled"
#define BASE_VALUE    200
#define CHARGE_VALUE  777

int charges;

create_object()
{
    charges = 3;
      set_name("star");
    set_short("diamond sprinkled star");
    add_adj(({"diamond", "sprinkled"}));
    set_long(
        "You are looking at a diamond sprinkled star! It looks like " +
        "a very valuable item.\n");
    add_prop(OBJ_I_VALUE, "@@value");
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME, 250);
    add_prop(MAGIC_AM_MAGIC, ({ 45, "magic" }));
    add_prop(MAGIC_AM_ID_INFO, ({
        "It looks like this star is magical!\n", 1,
        "It seems like the sprinkles of the star are loose.\n", 30,
        "You can 'wave star over <item>', to sprinkle the <item>.\n", 75
            }));
}

int
value() {
    return BASE_VALUE + charges * CHARGE_VALUE;
}

init()
{
    ::init();
    add_action("do_sprinkle", "sprinkle");
    add_action("do_wave", "wave");
}

int
sprinkle(object obj, object with)
{
    string verb = query_verb();

    if (with != TO)
        return 0;
    if (ENV(with) != TP)
        return notify_fail("You have to hold it.\n");
    if (obj->query_prop(IS_SPRINKLED))
        return notify_fail("It is already sprinkled with diamonds!\n");
    if (--charges <= 0)
        return notify_fail("Nothing seems to happen!\n");

    if (living(obj)) {
        if (verb == "wave")
            TP->catch_msg("You wave the " + short() + " over " +
                  (TP == obj ? "yourself" : QTNAME(obj)) + ".\n");

        if (TP == obj) {
            write("You " + verb + " yourself with nice diamonds!\n");
            say(QCTNAME(TP) + " " + verb + "s " + HIM_HER(TP) +
                "self with nice diamonds!\n", TP);
        } else {
            TP->catch_msg("You " + verb + " " + QTNAME(obj) +
                          " with nice diamonds!\n");
            obj->catch_msg(QCTNAME(TP) +
                           " " + verb + "s you with nice diamonds!\n");
            say(QCTNAME(TP) + " " + verb + "s " + QTNAME(obj) +
                " with diamonds!\n", ({ obj, TP }));
        }
        return 1;
    }

    if (verb == "wave")
        write("You wave the " + short() + " over the " +
              obj->short() + ".\n");
    else
        write("You " + verb + " the " + obj->short() + " with your " +
              with->short() + "!!\n");

    say(QCTNAME(TP) + " waves " + HIS_HER(TP) + " " + QSHORT(with) +
        " over the " + QSHORT(obj) + "!\n", TP);

    tell_room(ETP,
              "The " + QSHORT(obj) + " gets covered with magical diamonds!!\n",
              TP);
    obj->set_short(obj->query_short() + " (sprinkled with diamonds)");
    obj->set_long(obj->query_long() +
                  " - It seems to be sprinkled with diamonds!!\n");
    obj->add_prop(OBJ_I_VALUE, obj->query_prop(OBJ_I_VALUE) + CHARGE_VALUE);
    obj->add_prop(IS_SPRINKLED, 1);
   if(obj->query_prop("_lost_alchemist_magnifying_glass_"))
     obj->get_the_alchemist();
    return 1;
}

int
do_sprinkle(string arg)
{
    object obj, with;

    notify_fail("Sprinkle what with what?\n");
    if (!strlen(arg) ||
        !parse_command(arg, INV(TP)+INV(ETP), "%o 'with' %o", obj, with)) {
        if (parse_command(arg, INV(ETP), "%o [with] [diamonds]", obj))
            with = TO;
        else
            return 0;
    }
    return sprinkle(obj, with);
}

int
do_wave(string arg)
{
    object obj, with;

    notify_fail("Wave what?\n");
    if (!strlen(arg) ||
        !parse_command(arg, INV(TP)+INV(ETP), "%o 'over' %o", with, obj))
            return 0;

    return sprinkle(obj, with);
}

