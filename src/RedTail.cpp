#include "RedTail.hpp"

RedTail::RedTail() {
    m_leftWing.SetTexture(GetAssets().GetTexture(TextureId::Wing));
    m_rightWing.SetTexture(GetAssets().GetTexture(TextureId::Wing));
    m_leftWing.SetModel(GetAssets().GetModel(ModelId::Wing));
    m_rightWing.SetModel(GetAssets().GetModel(ModelId::Wing));
    m_engine.SetModel(GetAssets().GetModel(ModelId::Engine));
    m_engine.SetTexture(GetAssets().GetTexture(TextureId::Engine));
    m_leftWing.SetPosition({0.83, 0, 0});
    m_rightWing.SetPosition({0.83, 0, 0});
    m_leftWing.SetScale({-1, 1, -1});
    m_rightWing.SetScale({1, 1, -1});
    m_engine.SetScale({1, 1, -1});
    m_engine.SetRotation(glm::radians(-40.f), {1, 0, 0});
    m_engine.SetPosition({0.f, 0.f, 0.22f});
    m_leftWing.SetRotation(glm::radians(-40.f), {1, 0, 0});
    m_rightWing.SetRotation(glm::radians(-40.f), {1, 0, 0});
}
