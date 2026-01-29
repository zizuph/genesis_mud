#define FALSE 0
#define TRUE 1

private mapping logic;

private nomask object make_atom(string atom_name, status truth)
{
    object atom = clone_object("atom");
    atom->set(atom_name, truth);
    return atom;
}

private nomask object make_literal(string atom_name, status truth)
{
    object literal = clone_object("literal");
    literal->set(atom_name, truth);
    return literal;
}

private nomask object make_rule(object head, object *body)
{
    object rule = clone_object("rule");
    rule->set(head, body);
    return rule;
}

private nomask void invoke_rule(string rule_name);

nomask mixed set_atom(string atom_name, status truth, mixed params)
{
    int i;
    object atom = logic[atom_name];
    atom->set_truth(truth);
    atom->set_return_value(truth ? atom->funct(params) : 0);
    for (i = 0; i < sizeof(atom->query_body_rule_list()); ++i)
	invoke_rule(atom->query_body_rule_list()[i]);
    return atom->query_return_value();
}

private nomask void invoke_rule(string rule_name)
{
    int i, truth = TRUE;
    object *body = logic[rule_name]->query_body();
    mixed *params = ({ });
    for (i = 0; i < sizeof(body); ++i)
    {
	mixed *atom = logic[body[i]->query_atom_name()];
	truth &= body[i]->query_truth() == atom->query_truth();
	params += ({ atom->query_return_value() });
    }
    if (truth)
    {
	mixed *head = logic[rule_name]->query_head();
	set_atom(head->query_atom_name(), head->query_truth(), params);
    }
}

nomask void add_atom(string atom_name, status truth, mixed params)
{
    logic[atom_name] = clone_object(atom_name);
    set_atom(atom_name, truth, params);
}

nomask void add_rule(string rule_name, object head, object *body)
{
    int i;
    logic[rule_name] = make_rule(head, body);
    for (i = 0; i < sizeof(body); ++i)
    {
	string *body_rule_list =
		logic[body[i]->query_atom_name()]->query_body_rule_list();
	body_rule_list += ({ rule_name });
    }
    invoke_rule(rule_name);
}

nomask void remove_rule(string rule_name)
{
    int i;
    object *body = logic[rule_name]->query_body();
    for (i = 0; i < sizeof(body); ++i)
    {
	string *body_rule_list =
		logic[body[i]->query_atom_name()]->query_body_rule_list();
	body_rule_list -= ({ rule_name });
    }
    logic[rule_name]->remove_object();
    logic[rule_name] = 0;
}
