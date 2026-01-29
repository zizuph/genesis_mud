#pragma save_binary

/*
 * Just a little file to catch attacks.
 */

void
attacked_by(object who) {
    ::attacked_by(who);
    relay(all_inventory(environment()), "attack_alert",
          0, (string)who->query_real_name());
}
