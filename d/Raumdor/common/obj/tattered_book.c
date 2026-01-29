/* 
 * 2018.03.25 (Shanoga)
 */

#include "defs.h"

#define RECOVER_PREFIX "TATTERED_BOOK"
#define SPELLCRAFT_REQUIRED 40
#define SKILL_TYPE SS_FORM_CONJURATION
// Per intact page:
#define SKILL_AMOUNT 5

inherit "/std/book.c";
inherit "/lib/holdable_item.c";

int bonus_applied, skill_bonus, *page_torn = allocate(3);

void
generate_pages()
{
    page_torn[0] = (random(5) > 2); // 60%
    page_torn[1] = !random(3);      // 66%
    page_torn[2] = !random(4);      // 75%
    skill_bonus = 0;
    foreach (int torn : page_torn)
        if (!torn)
            skill_bonus += SKILL_AMOUNT;
}

void
create_book()
{
    ::create_book();
    set_name("book");
    set_adj("brown");
    set_short("brown book");
    set_long("@@book_long_description@@");

    will_not_recover = (random(100) < PERCENTAGE_OF_RECOVERY_LOST);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 100 + (GOLD_VALUE * skill_bonus));

    add_prop(MAGIC_AM_MAGIC, ({50, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO,
      ({
        "When held by someone with sufficient magical ability, this book " +
        "further enhances their prowess.\n",
        20,
        "The pages themselves are useful when applied to conjuration " +
        "magic.\n",
        40,
        "Each page contributes to effect. If a page is in tatters, it is " +
        "useless.\n",
        50,
      }));
    add_prop(OBJ_S_WIZINFO,
      "This book can provide a bonus to the conjuration skills of up to 15. " +
      "The amount is randomly determined by the number of pages that remain " +
      "intact (3 pages, 5 levels each). It also provides a bonus of 5 to " +
      "spellcraft. A players be trained in spellcraft to above 40 (superior " +
      "acolyte) and be holding and be holding the book to receive theese " +
      "bonuses.\n");

    set_max_pages(3);
    set_slots(W_ANYH);
    generate_pages();
}

string
book_long_description()
{
    if (TP->query_skill(SS_SPELLCRAFT) < SPELLCRAFT_REQUIRED)
    {
        return "This is an old book with a faded brown cover and tattered " +
               "pages.\n";
    }
    return "This is an old book with a faded brown cover and tattered pages. " +
           "It seems to be an ancient book of magic. There are dark patches " +
           "on the binding from ages of use.\n";
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public mixed
hold(object ob)
{
    object player;
    if (TP->query_skill(SS_SPELLCRAFT) < SPELLCRAFT_REQUIRED)
    {
        bonus_applied = 0;
        return 0;
    }
    bonus_applied = skill_bonus;
    player = query_holder();
    player->set_skill_extra(
      SKILL_TYPE, player->query_skill_extra(SKILL_TYPE) + skill_bonus);
    player->set_skill_extra(
      SS_SPELLCRAFT, player->query_skill_extra(SS_SPELLCRAFT) + 5);
    player->catch_msg(
      "As you take the book in hand, a tingling feeling travels through your " +
      "arm up to your mind, bringing clarity and a stronger connection to " +
      "the magical planes.\n");
    return 0;
}

public mixed
release(object ob)
{
    object player;
    if (!bonus_applied)
        return 0;
    player = query_holder();
    player->set_skill_extra(
      SKILL_TYPE, player->query_skill_extra(SKILL_TYPE) - bonus_applied);
    player->set_skill_extra(
      SS_SPELLCRAFT, player->query_skill_extra(SS_SPELLCRAFT) - 5);
    player->catch_msg(
      "You release the book and feel your connection to the magical planes " +
      "diminish.\n");
    return 0;
}

varargs void
read_book_at_page(int which, string verb)
{
    string page_file = COMMON_TEXT_DIR + "LICH_BOOK_" + which +
                       (page_torn[which - 1] ? "_TORN" : "_FULL") + ".txt";

    seteuid(getuid(TO));
    cat(page_file);
}

string
query_recover()
{
    int torn = page_torn[0] | (page_torn[1] << 1) | (page_torn[2] << 2);

    return MASTER + ":#" + RECOVER_PREFIX + "#" + torn + "#";
}

public void
init_recover(string arg)
{
    string trash;
    int torn;
    sscanf(arg, "%s#" + RECOVER_PREFIX + "#%d#s", trash, torn, trash);
    page_torn[0] = torn & 0x1;
    page_torn[1] = torn & 0x2;
    page_torn[2] = torn & 0x4;
}
