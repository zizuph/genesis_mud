/* -*-C++-*-
 * file name:     /d/Avenir/inherit/emote_hook.c
 * creator(s):    Grace 1995
 * purpose:       hook on various emotions made easy
 * note:          This function is from Krynn's monster.c 
 *
 */
#pragma strict_types
#pragma save_binary


/* Example 
 *
 * inherit "/d/Avenir/inherit/monster"
 * inherit "/d/Avenir/inherit/emote_hook"
 *
 * void 
 * create_monster()
 * {
 *
 *     add_emote_hook("smile", 1.5, do_smile);
 *     add_emote_adverb_hook("shyly", 2.0, do_smile);
 * }
 *
 * public void
 * do_smile(object actor, string adverb)
 * {
 *     command("smile shyly at "+ actor->query_name());
 * }
 *
 */

mapping gNpc_emotes = ([]), gNpc_adverbs = ([]);

public mapping
query_emotes()
{
    return secure_var(gNpc_emotes);
}

public mapping
query_emotes_adverb()
{
    return secure_var(gNpc_adverbs);
}

public void
add_emote_hook(string emote, float time, function func)
{
    if (gNpc_emotes[emote])
        gNpc_emotes = m_delete(gNpc_emotes, emote);

    gNpc_emotes += ([ emote : ({ time, func }) ]);
}

public void 
emote_hook(string emote, object actor, string adverb) 
{ 
    mixed t; 
    function f; 
    if (pointerp((t = gNpc_emotes[emote]))) 
    { 
    f = t[1]; 
    set_alarm(t[0], 0.0, &f(actor, adverb)); 
    } 
    else 
    if (pointerp((t = gNpc_adverbs[adverb]))) 
    { 
        f = t[1]; 
        set_alarm(t[0], 0.0, &f(actor, emote)); 
    } 
}
