<a name="readme-top"></a>



<!-- PROJECT LOGO -->
<br />
<div align="center">
  <img src="Resources/XRPLToolsLogo.png" alt="Logo" >

  <h3 align="center">XRPL Unreal Engine Plugin</h3>

  <p align="center">
    XRPL Unreal Engine Plugin: Bridging Virtual Realities with Decentralized Finance!
    <br />
    <br />
    <a href="https://github.com/zachdolph/xrpl-unreal-engine-plugin/issues">Report Bug</a>
    ·
    <a href="https://github.com/zachdolph/xrpl-unreal-engine-plugin/issues">Request Feature</a>
  </p>
</div>

<!-- PROJECT SHIELDS -->
[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



## ⚠️ Currently in Development ⚠️

This plugin is currently in development, and not meant for production use just yet. Take a look at the roadmap section to see current progress as well as details on plans for the future.

<!-- TABLE OF CONTENTS -->
<details open>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#installation">Installation</a></li>
    <li><a href="#contributing">Contributing</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#acknowledgments">Acknowledgments</a></li>
  </ol>
</details>


<!-- ABOUT THE PROJECT -->
## About the XRPL Unreal Engine Plugin

The XRPL Unreal Engine Plugin provides a seamless integration of the XRP Ledger's powerful features into the world of Unreal Engine. Designed with both developers and end-users in mind, this plugin facilitates direct interactions with the XRP Ledger, enabling the creation of dynamic and immersive applications that can leverage cryptocurrency transactions, token operations, and other XRPL functionalities.

Whether you're building the next-gen decentralized game, creating a virtual marketplace, or simply wanting to incorporate the advanced capabilities of the XRP Ledger into your Unreal Engine project, our plugin streamlines the process, ensuring a smooth and optimized experience. With Blueprint-exposed RPC calls, intuitive templates, and comprehensive documentation, diving into the XRPL ecosystem has never been easier.

Join us in this journey to bridge the worlds of gaming, virtual realities, and decentralized finance, and unlock the unlimited potentials that lie therein.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



### Built With

[![Unreal][Unreal Engine]][Unreal-url]
[![C++][CPP]][CPP-url]

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ROADMAP -->
## Roadmap

### Testnet Integration & Foundation
- [ ] XRPL Node Connection Settings and Basic Status Checks
    - **Timeline:** Month 1
- [ ] Wallet ID / Address Input and Secret/Passphrase Input
    - **Timeline:** Month 1
- [ ] Implement Blueprint-Exposed RPC Calls (account_info, sign, submit)
    - **Timeline:** Month 1

### Core Functionality & Blueprint Integration
- [ ] Develop Templates for Sending XRP and Setting Trust Lines
    - **Timeline:** Month 2
- [ ] Templates for Issuing IOUs and Basic Notifications for Transaction Outcomes
    - **Timeline:** Month 2
- [ ] Setup Basic Debugging and Logging
    - **Timeline:** Month 2
- [ ] Create Sample Blueprints for Implemented Templates
    - **Timeline:** Month 2

### Finalization & Public Beta Testing
- [ ] In-Editor Help Documentation and XRPL Explorer Links Integration
    - **Timeline:** Month 3
- [ ] Testing on different Unreal Engine versions and bug fixes
    - **Timeline:** Month 3
- [ ] Packaging, publishing, and deploying the plugin for UE4/UE5
    - **Timeline:** Month 3

See the [open issues](https://github.com/zachdolph/xrpl-unreal-engine-plugin/issues) for a full list of proposed features (and known issues).

<p align="right">(<a href="#readme-top">back to top</a>)</p>

<!-- GETTING STARTED -->
### Installation

#### 1. Download the Plugin Source
- Retrieve the source code from the official [GitHub repository](https://github.com/zachdolph/xrpl-unreal-engine-plugin.git).
- Extract the downloaded ZIP file to a preferred location.

#### 2. Integrate the Plugin into Your Project
- Navigate to the `xrpl-unreal-engine-plugin` directory from the extracted files.
- Copy its contents and paste them into your project's `Plugins` directory.

#### 3. Regenerate the Visual Studio Project Solution
- Once the plugin is integrated, right-click on your `.uproject` file.
- Select the option to regenerate the project solution. This action ensures that the Unreal Engine recognizes and correctly processes the new plugin.

#### 4. Compilation
- Open the newly generated Visual Studio solution.
- Compile the solution to build the plugin into your project.

#### 5. Activate the Plugin within the Unreal Engine Editor
- Start your project's Unreal Engine editor.
- To activate the plugin, navigate to *Settings* > *Edit Plugins* and locate "XRPL Tools". Ensure it's enabled.


<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTRIBUTING -->
## Contributing

Contributions are what make the open source community such an amazing place to learn, inspire, and create. Any contributions you make are **greatly appreciated**.

If you have a suggestion that would make this better, please fork the repo and create a pull request. You can also simply open an issue with the tag "enhancement".
Don't forget to give the project a star! Thanks again!

1. Fork the Project
2. Create your Feature Branch (`git checkout -b feature/AmazingFeature`)
3. Commit your Changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the Branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- LICENSE -->
## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- CONTACT -->
## Contact

Zach Dolph - [@ZachDolphDev](https://twitter.com/zachdolphdev)

[https://github.com/zachdolph/xrpl-unreal-engine-plugin](https://github.com/zachdolph/xrpl-unreal-engine-plugin)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- ACKNOWLEDGMENTS -->
## Acknowledgments

* [XRPL](https://xrpl.org/)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- MARKDOWN LINKS & IMAGES -->
[contributors-shield]: https://img.shields.io/github/contributors/zachdolph/xrpl-unreal-engine-plugin.svg?style=for-the-badge
[contributors-url]: https://github.com/zachdolph/xrpl-unreal-engine-plugin/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/zachdolph/xrpl-unreal-engine-plugin.svg?style=for-the-badge
[forks-url]: https://github.com/zachdolph/xrpl-unreal-engine-plugin/network/members
[stars-shield]: https://img.shields.io/github/stars/zachdolph/xrpl-unreal-engine-plugin.svg?style=for-the-badge
[stars-url]: https://github.com/zachdolph/xrpl-unreal-engine-plugin/stargazers
[issues-shield]: https://img.shields.io/github/issues/zachdolph/xrpl-unreal-engine-plugin.svg?style=for-the-badge
[issues-url]: https://github.com/zachdolph/xrpl-unreal-engine-plugin/issues
[license-shield]: https://img.shields.io/github/license/zachdolph/xrpl-unreal-engine-plugin.svg?style=for-the-badge
[license-url]: https://github.com/zachdolph/xrpl-unreal-engine-plugin/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/zachdolph
[Unreal Engine]: https://img.shields.io/badge/unrealengine-%23313131.svg?style=for-the-badge&logo=unrealengine&logoColor=white
[Unreal-url]: https://www.unrealengine.com/
[CPP]: https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white
[CPP-url]: https://cplusplus.com/
