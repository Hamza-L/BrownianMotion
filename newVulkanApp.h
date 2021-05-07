//
// Created by Hamza Lahmimsi on 2021-02-19.
//

#ifndef VULKANTESTING_NEWVULKANAPP_H
#define VULKANTESTING_NEWVULKANAPP_H

#define _USE_MATH_DEFINES

#include "vulkanWindow.h"
#include "vulkanPipeline.h"
#include "vulkanDevice.h"
#include "vulkanSwapChain.h"
#include "vulkanModel.h"
#include "shapes/Plane.h"
#include "shapes/Cube.h"
#include "shapes/Icosahedron.h"
#include "stb_image.h"

//glm
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/matrix_transform.hpp>

//std
#include <memory>
#include <vector>
#include <chrono>
#include <cmath>


namespace hva {

    class NewVulkanApp {
    public:
        static constexpr int WIDTH = 1.5*800;
        static constexpr int HEIGHT = 1.5*800;

        NewVulkanApp();
        ~NewVulkanApp();

        NewVulkanApp(const NewVulkanApp&) = delete;
        NewVulkanApp &operator=(const NewVulkanApp&) = delete;

        void run(std::string object);
        void rename(std::string name){
            vulkanWindow.rename(name);
        };
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void mouse_callback(GLFWwindow* window, int button, int action, int mods);
        std::vector<Vertex> subdivide(std::vector<Vertex> triangle);
        Node subdivideNode ( Node sourceNode);
    private:
        struct UboVP{
            glm::mat4 V;
            glm::mat4 P;
            glm::vec4 lightPos;
        }uboVP;

        struct Bird{
            std::vector<Vertex> birdVert;
            std::vector<uint32_t> birdInd;
            std::vector<Vertex> lineVert;
            std::vector<uint32_t> lineInd;
            std::vector<std::unique_ptr<VulkanModel>> objModels;
            std::unique_ptr<VulkanModel> birdModel;
            glm::vec2 position{};
            std::vector<glm::vec2> prevPos;
            float direction;
            float speed = 0.03f;
            float speed_x = 0.3f;
            float speed_y = 0.3f;
            int trailLength = 48;
            float h,w;

            explicit Bird(VulkanDevice& device) {
                Vertex v1,v2,v3;
                v1.position = 0.1f * glm::vec3(-0.1f, -0.2f, 0.0f);
                v2.position = 0.1f * glm::vec3(0.0f, 0.2f, 0.0f);
                v3.position = 0.1f * glm::vec3(0.1f, -0.2f, 0.0f);

                v1.colour = glm::vec4(1.0f);
                v2.colour = glm::vec4(1.0f);
                v3.colour = glm::vec4(1.0f);

                birdVert.push_back(v1);
                birdVert.push_back(v2);
                birdVert.push_back(v3);

                birdInd = {0,1,2};

                //objModels.push_back(std::make_unique<VulkanModel>(device, birdVert, birdInd, device.graphicsQueue(),
                                        //device.getCommandPool(),
                                        //0));

                birdModel = std::make_unique<VulkanModel>(device, birdVert, birdInd, device.graphicsQueue(),
                                                          device.getCommandPool(),
                                                          0);

                direction = 2 * M_PI * (static_cast <float> (rand()) / static_cast <float> (RAND_MAX));
                speed_x = speed * cos(direction);
                speed_y = speed * sin(direction);

            }

            void move(){
                speed_x = speed * cos(direction);
                speed_y = speed * sin(direction);
                float x2 = position.x + speed_x * 0.1f; //new position
                float y2 = position.y + speed_y * 0.1f; //new position
                x2 = glm::mod(x2 +w,2.0f*w) -w;
                y2 = glm::mod(y2 +h,2.0f*h) -h;

                glm::mat4 birdMove;

                if (abs(x2-position.x)>=0.2 || abs(y2-position.y)>=0.2) {
                    birdMove = glm::translate(glm::mat4(1.0f), glm::vec3(x2, y2, 0.0f));
                } else {
                    glm::vec2 v2 = glm::vec2(x2-position.x,y2-position.y);
                    glm::vec2 v1 = glm::vec2(1.0f,0.0f);
                    float angle = glm::degrees(glm::orientedAngle(glm::normalize(glm::vec3(v2,0.0f)), glm::normalize(glm::vec3(v1,0.0f)),glm::vec3(0.0f,0.0f,1.0f)));
                    birdMove = glm::translate(glm::mat4(1.0f), glm::vec3(x2, y2, 0.0f)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(-angle - 90),
                                           glm::vec3(0.0f, 0.0f, 1.0f));
                }

                birdModel->setModel(birdMove);
                position.x = x2;
                position.y = y2;
                if (prevPos.size()<trailLength) {
                    prevPos.insert(prevPos.begin(), position);
                } else if (prevPos.size()>=trailLength){
                    prevPos.pop_back();
                    prevPos.insert(prevPos.begin(), position);
                }
            }

            void move(float inSpeed_x, float inSpeed_y){
                speed_x = speed * cos(direction) + inSpeed_x;
                speed_y = speed * sin(direction) + inSpeed_y;
                direction = glm::orientedAngle(glm::normalize(glm::vec3(1.0f,0.0f,0.0f)),
                                                 glm::normalize(glm::vec3(speed_x,speed_y,0.0f)), glm::vec3(0.0f, 0.0f, 1.0f));
                float x2 = position.x + speed_x * 0.1f; //new position
                float y2 = position.y + speed_y * 0.1f; //new position
                x2 = glm::mod(x2 +w,2.0f*w) -w;
                y2 = glm::mod(y2 +h,2.0f*h) -h;

                glm::mat4 birdMove;

                if (abs(x2-position.x)>=0.2 || abs(y2-position.y)>=0.2) {
                    birdMove = glm::translate(glm::mat4(1.0f), glm::vec3(x2, y2, 0.0f));
                } else {
                    glm::vec2 v2 = glm::vec2(x2-position.x,y2-position.y);
                    glm::vec2 v1 = glm::vec2(1.0f,0.0f);
                    float angle = glm::degrees(glm::orientedAngle(glm::normalize(glm::vec3(v2,0.0f)), glm::normalize(glm::vec3(v1,0.0f)),glm::vec3(0.0f,0.0f,1.0f)));
                    birdMove = glm::translate(glm::mat4(1.0f), glm::vec3(x2, y2, 0.0f)) *
                               glm::rotate(glm::mat4(1.0f), glm::radians(-angle - 90),
                                           glm::vec3(0.0f, 0.0f, 1.0f));
                }

                birdModel->setModel(birdMove);
                position.x = x2;
                position.y = y2;
                if (prevPos.size()<trailLength) {
                    prevPos.insert(prevPos.begin(), position);
                } else if (prevPos.size()>=trailLength){
                    prevPos.pop_back();
                    prevPos.insert(prevPos.begin(), position);
                }
            }

            void trail(VulkanDevice &device){
                if(objModels.size()<=1){
                    return;
                }

                std::vector<Vertex> newBirdVert;
                std::vector<uint32_t> newBirdInd;

                if(!lineVert.empty()) {
                    newBirdVert.push_back(lineVert[0]);
                    newBirdVert.push_back(lineVert[1]);
                    newBirdInd.push_back(0);
                    newBirdInd.push_back(1);
                    newBirdInd.push_back(0);
                }

                for (int i=1; i<prevPos.size(); i++) {

                    float x2 = prevPos[i].x; //new position
                    float y2 = prevPos[i].y; //new position

                    Vertex newV,prevV;
                    x2 = glm::mod(x2 + w,2.0f*w) -w;
                    y2 = glm::mod(y2 + h,2.0f*h) -h;
                    newV.position = glm::vec3(x2,y2, 0.0f);
                    newV.colour = glm::vec4(1.0f-sqrt(float(i)/float(trailLength)),0.0f,0.0f,1.0f);

                    x2 = prevPos[i-1].x; //new position
                    y2 = prevPos[i-1].y; //new position

                    x2 = glm::mod(x2 + w, 2.0f * w) -w;
                    y2 = glm::mod(y2 + h, 2.0f * h) -h;
                    prevV.position = glm::vec3(x2,y2, 0.0f);
                    prevV.colour = glm::vec4(1.0f-sqrt(float((i-1))/float(trailLength)),0.0f,0.0f,1.0f);

                    if(abs(glm::distance(newV.position,prevV.position))<0.5f) {
                        newBirdVert.push_back(prevV);
                        newBirdVert.push_back(newV);

                        newBirdInd.push_back(2 * (i+1) - 2);
                        newBirdInd.push_back(2 * (i+1) - 1);
                        newBirdInd.push_back(2 * (i+1) - 2);
                    }

                }
                    objModels[1]->updateModel(newBirdVert,newBirdInd);
            }

            void colour(glm::vec4 colour){
                std::vector<Vertex> newBirdVert;
                for(Vertex v : birdVert){
                    v.colour = colour;
                    newBirdVert.push_back(v);
                }
                birdVert = newBirdVert;
                birdModel->updateModel(birdVert,birdInd);
            }

            void addLine(VulkanDevice& device,glm::vec2 p){
                Vertex v1,v2;
                v1.position = glm::vec3(position, 0.0f);
                v1.colour = glm::vec4(glm::vec3(0.005f),1.0f);
                v2.position = glm::vec3(p, 0.0f);
                v2.colour = glm::vec4(glm::vec3(0.005f),1.0f);

                lineVert.push_back(v1);
                lineVert.push_back(v2);

                lineInd.push_back(lineVert.size()-2);
                lineInd.push_back(lineVert.size()-1);
                lineInd.push_back(lineVert.size()-2);
            }

            void resetLine(){
                lineVert.clear();
                lineInd.clear();
                objModels.resize(1);
            }

            void setLine(VulkanDevice &device){
                if(objModels.size()==1 && lineInd.size()>=3) {
                    objModels.push_back(std::make_unique<VulkanModel>(device, lineVert, lineInd, device.graphicsQueue(),
                                                                      device.getCommandPool(),
                                                                      0));
                }else if(lineInd.size()>3){
                    objModels[1]->updateModel(lineVert,lineInd);
                }
            }
        };
        glm::mat4 M1 = glm::mat4(1.0f);
        void loadModels();
        void createPipelineLayout();
        void createDescriptorSetLayout();
        void createPushConstantRange();
        void createPipeline(int flag);
        void createCommandBuffers();
        void recordCommand(uint32_t imageIndex);
        void createUniformBuffers();
        void createDescriptorPool();
        void createDescriptorSets();
        void updateUniformBuffers(uint32_t imageIndex);
        void allocateDynamicBufferTransferSpace();
        void recreateSwapchain();
        void drawFrame();
        void updateModels();
        stbi_uc * loadTextureFile(std::string filename, int* width, int* height, VkDeviceSize* imageSize);
        int createTextureImage(std::string filename, std::string norm); //return id of the texture array
        int createTexture(std::string fileName, std::string norm);
        void createTextureSampler();
        int createTextureDescriptor(VkImageView texImage);
        int createTextureAndNormDescriptor(VkImageView texImage, VkImageView normImage);

        std::vector<std::unique_ptr<Bird>> flock;
        std::vector<std::unique_ptr<Bird>> distIndicators;

        std::vector<Vertex> getNormals(std::vector<Vertex> shape);

        VulkanWindow vulkanWindow{WIDTH, HEIGHT, "VulkanApp"};
        VulkanDevice device{vulkanWindow};
        std::unique_ptr<VulkanSwapChain> vulkanSwapChain;

        PipelineConfigInfo pipelineConfig;

        std::vector<std::unique_ptr<VulkanPipeline>> vulkanPipelines;
        int pipelineIndex = 0;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;

        std::vector<VkBuffer> vpUniformBuffer; //create one for every command buffer (swapchain image) so we are assured we are not modifying the buffer as it is being read.
        std::vector<VkDeviceMemory> vpUniformBufferMemory;

        std::vector<VkBuffer> mDynUniformBuffer;
        std::vector<VkDeviceMemory> mDynUniformBufferMemory;

        VkDescriptorSetLayout descriptorSetLayout;
        VkDescriptorSetLayout samplerSetLayout;
        VkPushConstantRange pushConstantRange;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;
        VkDescriptorPool samplerDescriptorPool;
        std::vector<VkDescriptorSet> samplerDescriptorSets; //these ones are not 1:1 with each image but with each textures.

        //size_t modelUniformAlignment;
        //pushObject *modelTransferSpace;

        std::unique_ptr<VulkanModel> vulkanModel;
        std::vector<std::unique_ptr<VulkanModel>> modelList;

        //assets
        std::vector<VkImage> textureImages;
        std::vector<VkDeviceMemory> textureImageMemory;
        std::vector<VkImageView> textureImageViews;
        std::vector<VkImage> textureNormImages;
        std::vector<VkDeviceMemory> textureNormImageMemory;
        std::vector<VkImageView> textureNormImageViews;
        VkSampler texSampler;
    };
}

#endif //VULKANTESTING_NEWVULKANAPP_H
