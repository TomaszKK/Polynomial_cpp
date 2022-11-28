#include <iostream>
#include <vector>

using namespace std;

class Poly {
  private:
    vector<float> coef;
    vector<int> power;
    int findIndex(float) const;
    Poly& sortPowers();

  public:
    Poly();
    Poly(float number);
    Poly& operator=(Poly const& other);
    Poly(Poly const& other);

    friend ostream& operator<<(ostream&, Poly const&);
    float& operator[](unsigned int n);
    float operator[](unsigned int) const;

    friend Poly operator+(Poly, Poly const&);
    friend Poly operator-(Poly, Poly const&);
    friend Poly operator*(Poly const&, Poly const&);

    float operator()(float point) const;
    friend Poly operator-(Poly);

    ~Poly();
};
