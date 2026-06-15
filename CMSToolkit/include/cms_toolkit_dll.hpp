/**
 * @file   cms_toolkit_dll.hpp
 * @brief  CMS Cross-platform C++ utility toolkit dll head
 * @author HeZhijun4030
 * @date   2026-05-28
 */
#ifndef CMS_UTILS_DLL_HPP
#define CMS_UTILS_DLL_HPP

#define CMS_Ver "1.0.5"

#ifdef _WIN32
#ifdef CMS_EXPORTS
#define CMS_API __declspec(dllexport)
#else
#define CMS_API __declspec(dllimport)
#endif
#else
#define CMS_API
#endif

#include <iostream>
#include <limits>
#include <string>
#include <chrono>

namespace cms
{
    CMS_API void Init();

    namespace structs::geometry
    {
/**
 * @brief 2D vector structure for basic geometric operations
 *
 * This structure provides a complete set of vector arithmetic operations,
 * including addition, subtraction, scalar multiplication, increment/decrement,
 * and comparison operators. It's designed for game development, GUI positioning,
 * and general 2D geometry calculations.
 *
 * @note All operations are performed on integers with no overflow checking
 * @note Operators are designed for intuitive syntax (e.g., v1 + v2, v1 += v2)
 * @warning The << and >> operators are overloaded for accumulation, not bit shifting
 * @see Position
 */
struct Vector
{
    int x; /**< X coordinate component */
    int y; /**< Y coordinate component */

    /**
     * @brief Default constructor
     * @post x = 0, y = 0
     */
    Vector():x(0),y(0){}

    /**
     * @brief Parameterized constructor
     * @param X Initial x coordinate value
     * @param Y Initial y coordinate value
     * @post x = X, y = Y
     */
    Vector(const int X,const int Y):x(X),y(Y){}

    // ------------------------------------------------------------------------
    // Getter/Setter Methods
    // ------------------------------------------------------------------------

    /**
     * @brief Sets the x coordinate with chainable syntax
     * @param X New x coordinate value
     * @return Reference to the current vector (for method chaining)
     *
     * @example
     * @code
     * Vector v;
     * v.SetX(5).SetY(10);  // Chainable
     * @endcode
     */
    Vector& SetX(const int X){this->x=X;return *this;}

    /**
     * @brief Sets the y coordinate with chainable syntax
     * @param Y New y coordinate value
     * @return Reference to the current vector (for method chaining)
     */
    Vector& SetY(const int Y){this->y=Y;return *this;}

    // ------------------------------------------------------------------------
    // Basic Arithmetic Operators
    // ------------------------------------------------------------------------

    /**
     * @brief Vector addition operator
     * @param v2 Vector to add
     * @return New vector containing element-wise sum
     *
     * @example
     * @code
     * Vector a(1,2), b(3,4);
     * Vector c = a + b;  // (4,6)
     * @endcode
     */
    Vector operator+(const Vector &v2)const{return Vector(this->x+v2.x,this->y+v2.y);}

    /**
     * @brief Vector addition assignment operator
     * @param v2 Vector to add
     * @return Reference to the modified vector
     *
     * @example
     * @code
     * Vector v(1,2);
     * v += Vector(3,4);  // v becomes (4,6)
     * @endcode
     */
    Vector& operator+=(const Vector &v2) {this->x += v2.x;this->y += v2.y;return *this;}

    /**
     * @brief Vector subtraction operator
     * @param v2 Vector to subtract
     * @return New vector containing element-wise difference
     */
    Vector operator-(const Vector &v2)const{return Vector(this->x-v2.x,this->y-v2.y);}

    /**
     * @brief Vector subtraction assignment operator
     * @param v2 Vector to subtract
     * @return Reference to the modified vector
     */
    Vector& operator-=(const Vector &v2) {this->x -= v2.x;this->y -= v2.y;return *this;}

    /**
     * @brief Scalar multiplication operator (vector * scalar)
     * @param scalar Integer scalar multiplier
     * @return New vector with each component multiplied by scalar
     *
     * @example
     * @code
     * Vector v(2,3);
     * Vector result = v * 3;  // (6,9)
     * @endcode
     */
    Vector operator*(const int scalar) const { return Vector(x * scalar, y * scalar); }

    /**
     * @brief Scalar multiplication assignment operator
     * @param scalar Integer scalar multiplier
     * @return Reference to the modified vector
     */
    Vector& operator*=(const int scalar) { x *= scalar; y *= scalar; return *this; }

    /**
     * @brief Scalar multiplication operator (scalar * vector)
     * @param scalar Integer scalar multiplier
     * @param v Vector operand
     * @return New vector with each component multiplied by scalar
     *
     * @note This friend function enables commutative scalar multiplication
     */
    friend Vector operator*(const int scalar, const Vector& v) { return v * scalar; }

    // ------------------------------------------------------------------------
    // Accumulation Operators (<< and >>)
    // ------------------------------------------------------------------------

    /**
     * @brief Vector accumulation operator (left shift semantics)
     * @param v Vector to add
     * @return Reference to the current vector
     *
     * @note Overloaded for accumulation, not bit shifting
     * @warning This is non-standard operator overloading; use += for clarity
     * @see operator+=
     */
    Vector& operator<<(const Vector& v) {x += v.x;y += v.y;return *this;}

    /**
     * @brief Scalar accumulation operator
     * @param c Scalar value to add to both components
     * @return Reference to the current vector
     *
     * @example
     * @code
     * Vector v(1,2);
     * v << 3;  // v becomes (4,5)
     * @endcode
     */
    Vector& operator<<(const int c) {x += c;y += c;return *this;}

    /**
     * @brief Prefix increment operator
     * @return Reference to the incremented vector
     * @post x++, y++
     *
     * @example
     * @code
     * Vector v(1,2);
     * ++v;  // v becomes (2,3)
     * @endcode
     */
    Vector& operator++() {++this->x,++this->y;return *this;}

    /**
     * @brief Postfix increment operator
     * @return Copy of the original vector before increment
     * @post x++, y++
     */
    Vector operator++(int) {const Vector temp=*this;++(*this);return temp;}

    /**
     * @brief Vector decrement accumulation operator
     * @param v Vector to subtract
     * @return Reference to the current vector
     *
     * @warning Non-standard overloading; use -= for clarity
     */
    Vector& operator>>(const Vector& v) {x -= v.x;y -= v.y;return *this;}

    /**
     * @brief Scalar decrement accumulation operator
     * @param c Scalar to subtract from both components
     * @return Reference to the current vector
     */
    Vector& operator>>(const int c) {x -= c;y -= c;return *this;}

    /**
     * @brief Prefix decrement operator
     * @return Reference to the decremented vector
     * @post x--, y--
     */
    Vector& operator--() {--this->x,--this->y;return *this;}

    /**
     * @brief Postfix decrement operator
     * @return Copy of the original vector before decrement
     */
    Vector operator--(int) {const Vector temp=*this;--(*this);return temp;}

    // ------------------------------------------------------------------------
    // Special Operators
    // ------------------------------------------------------------------------

    /**
     * @brief Unary negation operator
     * @return New vector with both components negated
     *
     * @example
     * @code
     * Vector v(5,-3);
     * Vector neg = -v;  // (-5,3)
     * @endcode
     */
    Vector operator-() const {return Vector(-x, -y);}

    // ------------------------------------------------------------------------
    // Boolean/Comparison Operators
    // ------------------------------------------------------------------------

    /**
     * @brief Check if vector is zero (origin point)
     * @return true if x == 0 && y == 0, false otherwise
     */
    bool isZero() const {return (x == 0) && (y == 0);}

    /**
     * @brief Equality comparison operator
     * @param v Vector to compare with
     * @return true if both components are equal, false otherwise
     */
    bool operator==(const Vector& v) const {return (x == v.x) && (y == v.y);}

    /**
     * @brief Inequality comparison operator
     * @param v Vector to compare with
     * @return true if any component differs, false otherwise
     */
    bool operator!=(const Vector& v) const {return (x != v.x) || (y != v.y);}
};

    /**
     * @brief Vector addition with scalar (vector + scalar)
     * @param v Vector operand
     * @param scalar Scalar value to add to both components
     * @return New vector with each component increased by scalar
     *
     * @example
     * @code
     * Vector v(2,3);
     * Vector result = v + 5;  // (7,8)
     * @endcode
     */
    inline Vector operator+(const Vector& v, const int scalar) {
        return Vector(v.x + scalar, v.y + scalar);
    }

    /**
     * @brief Vector addition with scalar (scalar + vector)
     * @param scalar Scalar value to add to both components
     * @param v Vector operand
     * @return New vector with each component increased by scalar
     *
     * @note Provides commutativity for scalar addition
     */
    inline Vector operator+(const int scalar, const Vector& v) {
        return v + scalar;
    }

    /**
     * @brief Alias for Vector to provide semantic meaning in positioning contexts
     *
     * @example
     * @code
     * Position pos(10, 20);  // Equivalent to Vector(10,20)
     * @endcode
     */
    typedef cms::structs::geometry::Vector Position;



        }






    namespace terminal
    {
        /**
         * @brief Clear terminal screen in Linux or Windows
         */
        CMS_API void ClearScreen();
    }

    namespace io
    {
        /**
         * @brief Clear input when error was happened
         */
        CMS_API void ClearInput();

        /**
         * @brief Safely reads user input with EOF detection
         * @tparam T      Target data type
         * @param Prompt  Prompt message to display
         * @return T      Valid input value
         * @throws std::runtime_error If input stream reaches EOF
         *
         * @note  Performs type validation and extra character detection
         * @warning Does NOT support std::string type
         * @see ClearInput()
         */
        template <typename T>
        T SafeInput(const std::string& Prompt)
        {
            T Result;
            while (true)
            {
                std::cout << Prompt;if (std::cin.eof())throw std::runtime_error("Input stream closed unexpectedly");
                if (std::cin >> Result)
                {
                    int next = std::cin.peek();if (next != '\n' && next != EOF){std::cout << "Extra characters detected, please try again" << std::endl;ClearInput();continue;}return Result;
                }
                std::cout << "Input type error, please try again" << std::endl;ClearInput();

            }
        }//SafeInput
    }
} // namespace cms

#endif // CMS_UTILS_DLL_HPP
