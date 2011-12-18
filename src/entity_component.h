#ifndef _ENTITY_COMPONENT_H
#define _ENTITY_COMPONENT_H

#include <map>
#include <string>

class EntityComponent {
private:
	const unsigned short component_type;

protected:
	EntityComponent(unsigned short component_type);

public:
	virtual ~EntityComponent();

	unsigned short get_component_type();
};

#endif
