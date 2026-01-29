/* 
 * This is a magical piece of equipment for the lich boss to hold. There is
 * a spellcraft requirement to hold it and gain the skill bonuses. The bonus
 * is random, depending on how many pages are intact.
 *
 * Worn By: /d/Raumdor/common/npc/lich.c
 *
 * Updated 2018.03.25 (Shanoga)
 */

#include "defs.h"

#define SPELLCRAFT_REQUIRED 40
#define SKILL_TYPE          SS_FORM_CONJURATION
// Per intact page:
#define SKILL_AMOUNT        5

inherit "/std/book.c";
inherit "/lib/holdable_item.c";
inherit "/lib/keep.c";

int bonus_applied, skill_bonus, *page_torn = allocate(3);

void
generate_pages()
{
    page_torn[0] = (random(5) > 2); // 60%
    page_torn[1] = !random(3);      // 66%
    page_torn[2] = !random(4);      // 75%
    skill_bonus = 0;
    foreach (int torn: page_torn)
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

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_VALUE, 100 + (GOLD_VALUE * skill_bonus));

    add_prop(MAGIC_AM_MAGIC, ({50, "conjuration"}));
    add_prop(MAGIC_AM_ID_INFO, ({
      "When held by someone with sufficient magical ability, " +
      "this book further enhances their prowess.\n", 20,
      "The pages themselves are useful when applied to conjuration magic.\n", 40,
      "Each page contributes to effect. If a page is in tatters, it is useless.\n", 50,
    }));
    add_prop(OBJ_S_WIZINFO, "This book can provide a bonus to the conjuration skills of " +
      "up to 15. The amount is randomly determined by the number of pages that remain " +
      "intact (3 pages, 5 levels each). It also provides a bonus of 5 to spellcraft. " +
      "A player must be trained in spellcraft to above 40 (superior acolyte) " +
      "and be holding the book to receive these skill point bonus.\n");

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
    return "This is an old book with a faded brown cover and tattered " +
          "pages. It seems to be an ancient book of magic. There are dark " +
          "patches on the binding from ages of use.\n";
}

/*
 * Function name: leave_env
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function leave_env() as copy of this function. It MUST
 *                make the call to holdable_item_leave_env(from, to) as well.
 *                If you omit this, then the item will not be automatically
 *                released when the player drops it, for instance.
 * Arguments    : object from - the environment we are leaving.
 *                object to   - the environment we are entering.
 */
void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

/*
 * Function name: appraise_object
 * Description  : When you inherit /lib/holdable_item.c you MUST also define
 *                the function appraise_object() as copy of this function. It
 *                MUST make the call to appraise_holdable_item() as well. If
 *                you omit this, then the player will not be able to appraise
 *                this item properly.
 * Arguments    : int num - the semi-randomised appraise skill.
 */
void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

public mixed
hold(object ob)
{
    
    if (TP->query_skill(SS_SPELLCRAFT) < SPELLCRAFT_REQUIRED)
    {
        bonus_applied = 0;
        return 0;
    }

    bonus_applied = skill_bonus; 
    E(TO)->set_skill_extra(SKILL_TYPE,
      TP->query_skill_extra(SKILL_TYPE) + skill_bonus);
    E(TO)->set_skill_extra(SS_SPELLCRAFT,
      TP->query_skill_extra(SS_SPELLCRAFT) + 5);
    E(TO)->catch_vbfc("As you take the book in hand, a tingling feeling " +
      "travels through your arm up to your mind, bringing clarity and " +
      "a stronger connection to the magical planes.\n");
    return 1;
}

/*
 * Function name: release
 * Description  : Removes the bonus skill and special description when the
 *              : book is released
 * Arguments    : object ob - the book
 */
public mixed
release(object ob)
{
    if (!bonus_applied)
        return 0;
    E(TO)->set_skill_extra(SKILL_TYPE,
      TP->query_skill_extra(SKILL_TYPE) - bonus_applied);
    E(TO)->set_skill_extra(SS_SPELLCRAFT,
      TP->query_skill_extra(SS_SPELLCRAFT) - 5);
    E(TO)->catch_vbfc("You release the book and feel your connection to the " +
      "magical planes diminish.\n");
    return 1;
}

/*
 * Function name: read_book_at_page
 * Description:   should be redefined in your book. is called from read_me
 * Arguments:     which - read the book at which page
 *        verb  - If the player wanted to read it, or mread it.
 *            To mread something, you can look how the scoll.c does
 *            it in read_it() if needed.
 */
varargs void
read_book_at_page(int which, string verb)
{
    string page_file = COMMON_OBJ_TEXT_DIR + "LICH_BOOK_" + which +
        (page_torn[which - 1] ? "_TORN" : "_FULL") + ".txt";

    seteuid(getuid(TO));
    TP->more(read_file(page_file)); 
}

/*
 * Function name: query_recover
 * Description  : Sets the state of the pages.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + "&&" + page_torn[0] + "&&" + page_torn[1] + "&&" + page_torn[2];
}

/*
 * Function name: init_recover
 * Description  : Restores the initial page values
 * Arguments    : string - the recovery string.
 */
public void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    
    if (sizeof(a) > 1)
    {
        page_torn[0] = atoi(a[1]);
        page_torn[1] = atoi(a[2]);
        page_torn[2] = atoi(a[3]);
    }
}