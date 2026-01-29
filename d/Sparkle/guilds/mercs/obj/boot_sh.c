inherit "/std/shadow";

object gSheath;

public void set_sheath_object(object ob) { gSheath = ob; }
public object query_sheath_object() { return gSheath; }

void leave_env(object from, object to)
{
    shadow_who->leave_env(from, to);

    from->catch_tell("You untie your "+gSheath->short()+" and remove "+
        "it from your "+shadow_who->short()+".\n");
    gSheath->do_remove_silently();
    remove_shadow();
}

