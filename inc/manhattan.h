
class manhattan
{
    private:
        int x,y;
    public:
        manhattan(/* args */);
        ~manhattan();

        template <typename numeric>
        numeric initialize(numeric, numeric);
        template <typename numeric>
        numeric calculate();
};