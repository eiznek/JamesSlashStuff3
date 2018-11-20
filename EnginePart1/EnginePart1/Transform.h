#include <d3dx9math.h>
#define VECTOR2 D3DXVECTOR2

class Transform {

	private:
		VECTOR2 *position;

	public:
		void Translate(VECTOR2 translation);
		VECTOR2 GetPosition();
		Transform();
		virtual ~Transform();

};