inherit "/std/shadow";

void notify_you_killed_me(object ob)
{
 write("You killed me , motherfucker! - "+ob->query_name()+"\n");
 shadow_who->notify_you_killed_me(ob);
}

void remove_sh()
{
 remove_shadow();
}

