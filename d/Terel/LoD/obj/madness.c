inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <std.h>

#define TO        this_object()
#define TP        this_player()
#define ETO       environment(TO)
#define MIN_DUR   20
#define MAX_DUR   500
#define MAD_DELAY 10 + random(5)
#define SUBLOC    "mad_subloc"
#define DIR_CMDS  ({"n", "w", "s", "e", "nw", "ne", "sw", "se", "u", "d",\
                    "north", "west", "east", "south",\
                    "northwest", "northeast", "southwest", "southeast",\
                    "up", "down"})
#define ALLOWED   ({"quit", "commune", "save", "bug", "typo", "info"})

static int mad_id=0;
static object *ob, caster;

public string
get_rnd_dir()
{
    string *cmds;
    
    cmds = environment(ETO)->query_exit_cmds();
    
    if (sizeof(cmds) == 0) return "";
    
    return cmds[random(sizeof(cmds))];
}

/*
 * Function name: parse
 * Description:   Here all commands the player gives comes.
 * Argument:      str - The extra string the player sent.
 */
public int
parse(string str)
{
    string dir;
    
    if (ETO != TP) return 0;

    if (SECURITY->query_wiz_rank(TP->query_real_name())) {
        write("Since you already are mad enough to be a wizard this " +
              "mortal madness won't make it much worse for you.\n");
        return 0;
    }
    
    if (member_array(query_verb(), ALLOWED) >= 0)
        return 0;
    
    if (member_array(query_verb(), DIR_CMDS) >= 0) {
        if (random(3) == 0)
            TP->catch_msg("You feel just great!\n");
        dir = get_rnd_dir();
        command("$" + dir);
    } else {
        TP->catch_msg("You feel so great you can't do a thing!\n");
    }
    
    return 1;
}

/*
 * Function name: init
 * Description:   Called when meeting an object
 */
void
init()
{
    ::init();
    add_action(parse, "", 1);
}

public void
create_object()
{
    set_name("_madness_object");
    set_no_show();
    add_prop(OBJ_M_NO_DROP, 1);
}

public void
set_duration(int dur)
{
    if (dur < MIN_DUR) dur = MIN_DUR;
    if (dur > MAX_DUR) dur = MAX_DUR;
    set_alarm(itof(dur), -1.0, remove_object);
}

public void
set_friends(object *friends)
{
    ob = friends;
}

public void
set_caster(object ob)
{
    caster = ob;
}

public void
madness()
{
    int i;
    object *all, foe=0, room;
    string cmd;
    
    if (!living(ETO)) return;
    
    room = environment(ETO);
    
    switch (random(5)) {
        case 0:
            ETO->catch_msg("You smile happily.\n");
            tell_room(room, QCTNAME(ETO) + " grins madly at you.\n", ETO);
            break;
        case 1:
            ETO->catch_msg("You cheer enthusiastically.\n");
            tell_room(room, QCTNAME(ETO) + " growls madly at you.\n", ETO);
            break;
        case 2:
            ETO->catch_msg("You giggle merrily.\n");
            tell_room(room, QCTNAME(ETO) + " moans madly in front of you.\n",
                      ETO);
            break;
        case 3:
            ETO->catch_msg("You laugh.\n");
            tell_room(room, QCTNAME(ETO) + " laughs madly.\n", ETO);
            break;
        case 4:
            ETO->catch_msg("You feel just great.\n");
            tell_room(room, QCTNAME(ETO) + " seems to have lost " +
                      ETO->query_possessive() + " mind.\n", ETO);
            break;
    }
    
    if (ETO->query_attack()) return;
    
    all = all_inventory(room);
    all -= ({ ETO });
    
    if (sizeof(ob)) {
        for (i=0; i<sizeof(all); i++) {
            if (!living(all[i])) continue;
            if (member_array(all[i], ob) >= 0) {
                foe = all[i];
                break;
           }
        }
    }
    
    if (!foe) {
        for (i=0; i<sizeof(all); i++) {
            if (!living(all[i])) continue;
            foe = all[i];
            break;
        }
    }
    
    if (!foe || foe == caster) {
        cmd = get_rnd_dir();
        if (!strlen(cmd)) return;
        if (SECURITY->query_wiz_rank(ETO->query_real_name())) {
            ETO->catch_msg("You would have gone " + cmd +
                           " if you would have been mortal.\n");
        } else {
            ETO->command("$" + cmd);
        }
        return;
    }
    
    if (SECURITY->query_wiz_rank(ETO->query_real_name())) {
        ETO->catch_msg("You would have attacked " + QTNAME(foe) +
                       " if you would have been mortal.\n");
        return;
    }
    
    ETO->attack_object(foe);
    foe->catch_msg(QCTNAME(ETO) + " attacks you!\n");
    tell_room(room, QCTNAME(ETO) + " attacks " + QTNAME(foe) + "!\n",
              ({foe, ETO}));
}

public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (!dest || !living(dest)) return;
    
    dest->catch_msg("You suddenly feel just great!\n");
    tell_room(environment(dest), QCTNAME(dest) + " gets a mad look in " +
              dest->query_possessive() + " eyes.\n", dest);
    dest->add_subloc(SUBLOC, TO);
    if (!mad_id)
        set_alarm(itof(MAD_DELAY), itof(MAD_DELAY), madness);
}

public void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    
    if (mad_id) remove_alarm(mad_id);
    mad_id = 0;
    
    if (!from || !living(from)) return;
    
    from->catch_msg("You feel normal again.\n");
    tell_room(environment(from), QCTNAME(from) +
              " looks normal again.\n", from);
    from->remove_subloc(SUBLOC);
}

public string
show_subloc(string subloc, object carrier, object for_obj)
{
   string str;

   if (carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
       return "";
   if (for_obj == carrier)
       str = "You are feeling just great.\n";
   else
       str = capitalize(carrier->query_pronoun()) +
             " is looking really mad. You better stay away from " +
             carrier->query_objective() + "!\n";
   return str;
}
