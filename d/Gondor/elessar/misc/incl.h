poss(obj) {
	if (obj->query_gender_string() == "female") return "her";
	if (obj->query_gender_string() == "male") return "his";
	if (obj->query_gender_string() == "neuter") return "its";
}

subj(obj) {
	if (obj->query_gender_string() == "female") return "she";
	if (obj->query_gender_string() == "male") return "he";
	if (obj->query_gender_string() == "neuter") return "it";
}

obje(obj) {
	if (obj->query_gender_string() == "female") return "her";
	if (obj->query_gender_string() == "male") return "him";
	if (obj->query_gender_string() == "neuter") return "it";
}
