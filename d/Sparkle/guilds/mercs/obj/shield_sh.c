inherit "/std/shadow";

object gTabard;

public void set_tabard_object(object ob) { gTabard = ob; }
public object query_tabard_object() { return gTabard; }

void leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);

    from->catch_tell("You undrape your "+shadow_who->short()+".\n");
    gTabard->undrape_shield_silently(from);
    remove_shadow();
}

