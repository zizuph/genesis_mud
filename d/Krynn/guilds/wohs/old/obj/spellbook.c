/*
 * The Wizards of High Sorcery Spellbook.
 * 
 * Go away if you don't belong here.
 */
inherit "/std/book";
inherit "/d/Genesis/newmagic/spellcasting";

#include <files.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include "../guild.h";

#define B_RED        1
#define B_WHITE      2
#define B_BLACK      4 
#define B_INITIATE   8
#define B_FULL       (B_RED|B_WHITE|B_BLACK)
#define B_ALL        (B_RED|B_WHITE|B_BLACK|B_INITIATE)

#define ORDER_MAP ([ RED : B_RED, WHITE : B_WHITE, BLACK: B_BLACK, \
                     INITIATE: B_INITIATE ])

/*
 * An array of all spells the mortals can have.
 * ({ spell_name, brach_mask, level })
 *
 */
static mixed all_spells = ({
    ({ "merak", B_ALL, 1 }),
        ({ "spenkilus", B_ALL, 1}),
        ({ "consensus", B_FULL, 1 }),
        });


/* 
 * This mapping keeps track on how many more times we can
 * cast this spell.
 */
static mapping study;
static object study_spell;

public void
create_book()
{
    setuid();
    seteuid(getuid());

    set_name("book");
    add_name("spellbook");
    add_name(SPELL_BOOK);

    set_long("This is a red leather bound book with golden bindings. " + 
        "The leather cracks at the back of the book, due to wear and " +
        "intensive usage. Judging from the looks of the book, it must " + 
        "have been used for generation.\n");

    set_short("red leather bound book");
    set_adj(({"red", "leather", "leather bound"}));

    add_prop(OBJ_M_NO_DROP, "You should not drop this book, it is worth " + 
        "more then your life!\n");
    add_prop(OBJ_M_NO_GIVE, "You should not give this book away, it is " + 
        "worth more then your life!\n");
    
    study = ([ ]);

}

void
enter_env(object to, object from)
{
    int index;
    mixed list;
    ::enter_env(to, from);

    if (!ADMIN->query_member(to))
        return;

    
    add_spell_object(to);

    /* 
     * I filter out all spells with the wrong bit value 
     */
    list = filter(all_spells, 
        &operator(&)(ORDER_MAP[ADMIN->query_member_type(to)]) @ 
           &operator([])(, 1));

    /*
     * Then we filter out spells requiring a too high level
     */
    list = filter(list, &operator(<)(ADMIN->query_member_level(to)) @ 
        &operator([])(, 2));

    if (!sizeof(list))
        return 0;
    
    list = map(list, &operator(+)(SPELLS, ) @ &operator([])(, 0));
    map(list, add_spell);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    remove_spell_object(from);
}


public void
list_spells()
{
    int i;
    string *book_spells = m_indices(gSpells);
    string *memory_spells = m_indices(study);
    string desc;
    object ob;
    
    book_spells -= memory_spells;
    
    i = sizeof(memory_spells);
    if (!i)
        write("You have no spells remembered.\n");
    else
        write("You remember having studied:\n");

    while (i--)
    {
        if (ob = get_spell_object(memory_spells[i]))
        {
            desc = ob->query_spell_desc() || "";
            write(sprintf("  %-15s (%d) %s\n", 
                memory_spells[i], study[memory_spells[i]], desc));
        }
    }
    
    if (sizeof(book_spells))
    {
        write("You recall having " + 
            COMPOSITE_WORDS(map(book_spells, capitalize)) +
            " in your " + short() + ".\n");
    }
}

public void
modify_usage(string spell, int change)
{
    study[spell] += change;
    
    if (study[spell] <= 0)
        study = m_delete(study, spell);
    
}

void
study_stop(mixed arg)
{
    if (!arg || !objectp(study_spell))
    {
        /* Player stopped studying */
        return;
    }

    if (objectp(arg))
    {
        modify_usage(
                     study_spell->query_spell_name(), 
                     study_spell->study_spell(arg)
                     );
        return;
    }
}

int
study_cmd(string str)
{
    object ob;

    if (!stringp(str))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    str = lower_case(str);
    if (!gSpells[str] || 
        !objectp(ob = get_spell_object(str)))
    {
        notify_fail("You know no spell by the name " + 
            capitalize(str) + " that you could study.\n");
        return 0;
    }
    
    if (!ob->valid_study(this_player()))
    {
        return 1;
    }

    write("You begin to carefully study the magic of the spell " + 
        capitalize(str) + ".\n");
    say(QCTNAME(this_player()) + " begins reading his spellbook.\n");

    study_spell = ob;
    
    ob = clone_object(PARALYZE_OBJECT);
    ob->set_standard_paralyze("studying");
    ob->set_stop_fun("study_stop");
    ob->set_remove_time(30);
    ob->move(this_player(), 1);

    return 1;
}


void
init()
{
    ::init();

    add_action(study_cmd, "study");
}
