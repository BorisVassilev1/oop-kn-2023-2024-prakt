#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <functional>
#include <cassert>

struct vec3 {
	float x, y, z;
};

class Object3d {
	using uint = unsigned int;
	std::vector<vec3>			  vertices;
	std::vector<std::vector<uint>> indices;

	static std::ifstream openFileRead(const std::string &file) {
		std::ifstream ifs(file);
		if (!ifs) std::cout << "failed to open file for reading!" << std::endl;
		return ifs;
	}

	static std::ofstream openFileWrite(const std::string &file) {
		std::ofstream ofs(file);
		if (!ofs) std::cout << "failed to open file for writing!" << std::endl;
		return ofs;
	}

   public:
	Object3d() {}
	Object3d(const std::string &file) : Object3d(openFileRead(file)) {}

	Object3d(std::istream &&in) {
		char first;
		while (in >> first) {
			if (first == 'v') {
				first = in.get();
				vec3 vertex;
				in >> vertex.x >> vertex.y >> vertex.z;
				vertices.push_back(vertex);
			}
			else if (first == 'f') {
				indices.push_back({});
				int	 index;
				char nextSymbol;
				while ((nextSymbol = in.peek()) != '\n') {
					if (std::isspace(nextSymbol)) {
						in.get();
						continue;
					}
					in >> index;
					assert(index <= (int)vertices.size());
					indices.back().push_back(index);
				}
			} else {
				if(first != '#') {
					std::cout << "file invalid or corrupted" << std::endl;
					vertices.clear();
					indices.clear();
				}
			}
			in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	void print(std::ostream &&out) const {
		out << "# file created with OOP homework!!\n";
		for (const auto &v : vertices)
			out << std::fixed << "v " << v.x << " " << v.y << " " << v.z << "\n";

		for (const auto &face : indices) {
			out << "f ";
			for (const auto &v : face)
				out << v << " ";
			out << "\n";
		}
	}

	void save(const std::string &file) const { print(openFileWrite(file)); }

	Object3d cut(const std::function<bool(float, float, float)> &f) const {
		Object3d		 res;
		std::vector<int> destinationIndices;
		destinationIndices.resize(vertices.size(), 0);
		for (std::size_t i = 0; i < vertices.size(); ++i) {
			const vec3 &pos = vertices[i];
			if (f(pos.x, pos.y, pos.z)) {
				res.vertices.push_back(pos);
				destinationIndices[i] = res.vertices.size();
			}
		}

		for (const auto &face : indices) {
			bool flag = true;
			for (int v : face) {
				if (destinationIndices[v - 1] == 0) flag = false;
			}
			if (flag) {
				res.indices.push_back(face);
				for (std::size_t i = 0; i < face.size(); ++i) {
					res.indices.back()[i] = destinationIndices[face[i] - 1];
				}
			}
		}
		return res;
	}

	int getFaceCount() const { return indices.size(); }

	int getVertexCount() const { return vertices.size(); }

	void flip() {
		for(auto face : indices) {
			std::reverse(face.begin(), face.end());
		}
	}

	static Object3d makeCube(float size = 1.) {
		Object3d o;
		float	 s = size / 2;
		o.vertices.push_back(vec3(-s, -s, -s));
		o.vertices.push_back(vec3(s, -s, -s));
		o.vertices.push_back(vec3(s, -s, s));
		o.vertices.push_back(vec3(-s, -s, s));
		o.vertices.push_back(vec3(-s, s, -s));
		o.vertices.push_back(vec3(s, s, -s));
		o.vertices.push_back(vec3(s, s, s));
		o.vertices.push_back(vec3(-s, s, s));

		o.indices.push_back({1, 2, 3, 4});
		o.indices.push_back({8, 7, 6, 5});
		o.indices.push_back({1, 5, 6, 2});
		o.indices.push_back({2, 6, 7, 3});
		o.indices.push_back({3, 7, 8, 4});
		o.indices.push_back({4, 8, 5, 1});
		return o;
	}

	static Object3d makeSphere(float radius = 1) {
		Object3d o;
		uint		 detailX = 20;
		uint		 detailY = 20;

		uint vertexCount = (detailX * 2 + 1) * detailY;

		o.vertices.resize(vertexCount);
		for (uint i = 0; i < detailX; ++i) {
			float lon = i * M_PI / (detailX - 1);
			for (uint j = 0; j < detailY * 2 + 1; ++j) {
				float lat = j * M_PI / (detailY);

				int index = j + i * (detailY * 2 + 1);

				o.vertices[index]		= vec3(
					radius * sin(lon) * cos(lat),
					radius * cos(lon),
					radius * sin(lon) * sin(lat)
				);
			}
		}

		for (uint x = 0; x < detailX - 1; ++x) {
			for (uint y = 0; y < detailY * 2; ++y) {
				uint i = x * (detailY * 2 + 1) + y + 1;
				o.indices.push_back( {i    , i + 1                    , i + (detailY * 2 + 1) });
				o.indices.push_back( {i + 1, i + (detailY * 2 + 1) + 1, i + (detailY * 2 + 1) });
			}
		}

		return o;
	}
};

int main() {
	Object3d	  o("./homework/cube.obj");
	o.save("./homework/cube_2.obj");

	Object3d b("./homework/bunny.obj");
	b.save("./homework/bunny_2.obj");

	Object3d	  s("./homework/sphere.obj");
	s.save("./homework/sphere_2.obj");

	std::cout << "vertices: " << b.getVertexCount() << std::endl;
	std::cout << "faces: " << b.getFaceCount() << std::endl;

	Object3d b_cut = b.cut([](float x, float y, float) -> bool { return y - x < 2.5; });
	std::cout << "vertices: " << b_cut.getVertexCount() << std::endl;
	std::cout << "faces: " << b_cut.getFaceCount() << std::endl;
	b_cut.save("./homework/bunny_cut.obj");

	Object3d c("./homework/bunny_cut.obj");


	Object3d madeCube = Object3d::makeCube(2.);
	madeCube.save("./homework/cube_auto.obj");
	Object3d madeSphere = Object3d::makeSphere(2.);
	madeSphere.save("./homework/sphere_auto.obj");
}
