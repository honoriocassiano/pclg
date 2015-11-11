/*
 * Surface.h
 *
 *  Created on: 11 de nov de 2015
 *      Author: cassiano
 */

#ifndef SKY_SURFACE_H_
#define SKY_SURFACE_H_

namespace sky {

class Surface {
public:
	Surface();
	virtual ~Surface();

	virtual void show() = 0;
	virtual void update(float) = 0;
};

} /* namespace sky */

#endif /* SKY_SURFACE_H_ */
