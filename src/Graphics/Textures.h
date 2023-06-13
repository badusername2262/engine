
class Texture
{
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;

    virtual void Bind() const = 0;
};

class texture2D : Texture
{
    static std::reference_wrapper<Texture2D> Create(const std::string& path);
};