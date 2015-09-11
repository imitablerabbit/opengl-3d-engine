#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
	public:
		Material(float, float);
		Material();
		~Material();

		//Getters and setters
		float getReflectivity();
		float getDampening();
		void setReflectivity(float);
		void setDampening(float);

	private:
		float reflectivity;
		float dampening;

};

#endif