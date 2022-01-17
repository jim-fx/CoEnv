<script lang="ts">
	import { Slide, SlideTitle, BarChart, SlideProgress } from '$lib/components';
	import { coworkingGoogleTrendGermany, coworkingSpacesWorldWide } from '$lib/data';
	import { HexagonBackground, Logo } from '$lib/elements';
	import { CoEnvComponents, MapCologne, MegaTrends, Thanks, TimeToMarket } from '$lib/slides';
	import { nextSlide, previousSlide, showBackground, slideTitle } from '$lib/stores';
	import { scale, fade } from 'svelte/transition';

	function handleKeyDown({ key }: KeyboardEvent) {
		if (key === 'ArrowRight') {
			nextSlide();
		}
		if (key === 'ArrowLeft') {
			previousSlide();
		}
	}
</script>

<svelte:window on:keydown={handleKeyDown} />

<svelte:head>
	<title>{$slideTitle}</title>
</svelte:head>

<Slide title="CoEnv | Max Richter">
	<div center>
		<div class="half" transition:scale>
			<Logo animated />
		</div>
	</div>
</Slide>

<Slide title="%I Problem">
	<div center box-border style="padding: 0px 20vh" transition:fade>
		<h1 text-6xl>Shared spaces are amazing, but they come with some uncertainties</h1>
		<h2 italic>Is this Room open for me? Can I use that table? Can I talk to that person?</h2>
	</div>
</Slide>

<Slide title="%I What is CoEnv?">
	<div center box-border style="padding: 0px 20vh" transition:fade>
		<h1 text-6xl>CoEnv is an exploratory, modular ecosystem for shared environments,</h1>
		<h2 italic>with a focus on the individual user's needs</h2>
	</div>
</Slide>

<Slide steps={3} let:step let:title>
	<div center>
		<CoEnvComponents {step} {title} />
	</div>
</Slide>

<Slide title="%I Who is CoEnv for?">
	<div center box-border style="padding: 0px 20vh" transition:fade>
		<h1 text-6xl>Who is our customer?</h1>
		<h2 italic>
			Small to medium-sized shared spaces for example HackerSpaces, Social public Spaces and
			Coworking Spaces
		</h2>
	</div>
</Slide>

<Slide steps={2} let:step background={false} title="%I Market - Megatrends">
	<MegaTrends {step} />
</Slide>

<Slide title="%I Market - Development I">
	<div absolute top-5 left-5>
		<h1 transition:fade>Amount of Coworking Spaces until 2020</h1>
		<p>
			Deskmag. "Anzahl der Coworking Spaces weltweit von 2005 bis 2018 und Prognose bis 2020." <br
			/>
			23. Mai, 2019. Statista. Zugegriffen am 17. November 2021.
		</p>
	</div>
	<BarChart startYear={2005} prognoseAfterIndex="13" data={coworkingSpacesWorldWide} />
</Slide>

<Slide title="%I Market - Development II">
	<div absolute top-5 left-5>
		<h1 transition:fade>Google Trends: Coworking</h1>
		<p>Accessed 18. November 2021.</p>
	</div>

	<BarChart data={coworkingGoogleTrendGermany} />
</Slide>

<Slide steps={2} background={false} let:step title="%I Customers - Potential">
	<MapCologne {step} />
</Slide>

<Slide title="%I Product - Price">
	<div center>
		<h1 text-8xl>Prices</h1>

		<table text-4xl font-light>
			<thead font-bold>
				<td>Product</td>
				<td>Price</td>
			</thead>

			<tr>
				<td>Workshop</td>
				<td>800€</td>
			</tr>

			<tr>
				<td>Roomboard (per)</td>
				<td>90€</td>
			</tr>

			<tr>
				<td>Cube (per)</td>
				<td>70€</td>
			</tr>

			<tr>
				<td>Sigil (per)</td>
				<td>3€</td>
			</tr>
		</table>
	</div>
</Slide>

<Slide steps={4} let:step title="%I Product - TTM">
	<TimeToMarket {step} />
</Slide>

<Slide background={false}>
	<Thanks />
</Slide>

<style>
	.half {
		width: 50vh;
		height: 50vh;
	}
</style>
